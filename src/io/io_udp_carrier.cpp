#include "io_udp_carrier.h"

#include <new>

#include "common_address_ipv4.h"
#include "common_logger.h"
#include "io_socket_handler_mgr.h"

UdpCarrierHandler::UdpCarrierHandler(int fd)
	: IOSocketHandler(fd, fd)
{
	m_sock_len = sizeof(sockaddr_in);

	m_destination_list.clear();
}

UdpCarrierHandler::~UdpCarrierHandler()
{
	if (m_read_fd >= 0)
	{
		close(m_read_fd);
		m_read_fd = -1;
	}

	std::list<IPAddrV4 *>::iterator it;
	for (it = m_destination_list.begin(); it != m_destination_list.end(); it++)
	{
		IPAddrV4 *tmp = *it;
		delete tmp;
	}

	m_destination_list.clear();
}

struct sockaddr_in* UdpCarrierHandler::get_peer_address()
{
	return &m_peer_address;
}

void UdpCarrierHandler::set_recv_buffer(IOSocketBuffer* buffer)
{
	this->m_recv_buffer = buffer;
}

void UdpCarrierHandler::set_send_buffer(IOSocketBuffer* buffer)
{
	this->m_send_buffer = buffer;
}

void UdpCarrierHandler::set_data_input_callback(DataInputCallback func)
{
	this->m_data_input_callback = func;
}

bool UdpCarrierHandler::add_destination(const std::string &ip, const uint16_t& port)
{
	IPAddrV4 *dest = new (std::nothrow) IPAddrV4(ip, port);
	if (!dest)
	{
		return false;
	}

	std::unique_lock<std::mutex> lock(this->m_mutex);
	std::list<IPAddrV4 *>::iterator it;
	for (it = m_destination_list.begin(); it != m_destination_list.end(); it++)
	{
		IPAddrV4 *tmp = *it;
		if (*tmp == *dest)
		{
			delete dest;
			return true;
		}
	}

	m_destination_list.push_back(dest);
	return true;
}

bool UdpCarrierHandler::remove_destination(const std::string& ip, const uint16_t& port)
{
	std::unique_lock<std::mutex> lock(this->m_mutex);
	std::list<IPAddrV4 *>::iterator it = m_destination_list.begin();
	while(it != m_destination_list.end())
	{
		if((*it)->equals(ip, port))
		{
			delete (*it);
			it = m_destination_list.erase(it);
		}else
		{
			it++;
		}
	}

	return true;
}

bool UdpCarrierHandler::read_data()
{
	int read_length = 0;

	if (m_recv_buffer)
	{
		int ret = m_recv_buffer->read_udp_fd(m_read_fd, &read_length, &m_peer_address);
		if (ret == ERROR_OK && m_data_input_callback)
		{
			m_data_input_callback();
		}
		else
		{
			LOG_ERROR("udp carrier read fail");
		}
	}
	else
	{
		LOG_ERROR("please set the read buffer for protocol");
	}


	return true;
}

bool UdpCarrierHandler::write_data()
{
	if (m_send_buffer)
	{
		std::unique_lock<std::mutex> lock(this->m_mutex);
		int ret = m_send_buffer->write_all_udp_fd(m_write_fd, m_destination_list);
		if (ret != ERROR_OK)
		{
			LOG_ERROR("udp carrier write fail");
		}
	}
	else
	{
		LOG_ERROR("please set the write buffer for protocol");
	}

	IOSocketHandlerMgr::disable_write_data(this);
	return true;
}

bool UdpCarrierHandler::start()
{
	return IOSocketHandlerMgr::enable_read_data(this);
}

bool UdpCarrierHandler::on_event(struct epoll_event &event)
{
	//firstly, write
	if ((event.events & EPOLLOUT) != 0)
	{
		if (!write_data())
		{
			LOG_ERROR("the udp carrier write data error");
		}
	}

	//secondly, read
	if ((event.events & EPOLLIN) != 0)
	{
		if (!read_data())
		{
			LOG_ERROR("the udp carrier read data error");
		}
	}

	return true;
}

bool UdpCarrierHandler::notify_output_data()
{
	return IOSocketHandlerMgr::enable_write_data(this);
}

UdpCarrierHandler *UdpCarrierHandler::create(std::string bindIp, uint16_t bindPort, uint16_t ttl,
											 uint16_t tos)
{

	int buffer_size = 1024 * 8;
	int sock = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
	if ((sock < 0) || (fcntl(sock, F_SETFD, FD_CLOEXEC) == -1))
	{
		int err = errno;
		LOG_ERROR("fail to create socket: (%d) %s", err, strerror(err));
		return nullptr;
	}

	int one = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const void *)&one, sizeof(one)) != 0)
	{
		LOG_ERROR("fail to reuse address");

		close(sock);
		return nullptr;
	}

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (const void *)&one, sizeof(one)) != 0)
	{
		LOG_ERROR("fail to reuse port");

		close(sock);
		return nullptr;
	}

	if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (const void *)&buffer_size, sizeof(int)) != 0)
	{
		LOG_ERROR("fail to set receive buffer size");

		//close(sock);
		//return nullptr;
	}

	if (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (const void *)&buffer_size, sizeof(int)) != 0)
	{
		LOG_ERROR("fail to set send buffer size");

		//close(sock);
		//return nullptr;
	}

	int temp = tos;
	if (setsockopt(sock, IPPROTO_IP, IP_TOS, (const void *)&temp, sizeof(temp)) != 0)
	{
		int err = errno;
		LOG_WARNING("fail to set IP_TOS: %d; error was (%d) %s", tos, err, strerror(err));
	}

	if (bindIp == "")
	{
		bindIp = "0.0.0.0";
		bindPort = 0;
	}

	struct sockaddr_in bindAddress;
	memset(&bindAddress, 0, sizeof(bindAddress));
	bindAddress.sin_family = AF_INET;
	bindAddress.sin_addr.s_addr = inet_addr(bindIp.c_str());  //INADDR_ANY;
	bindAddress.sin_port = htons(bindPort);

	if (bindAddress.sin_addr.s_addr == INADDR_NONE)
	{
		LOG_ERROR("fail to bind on address %s:%d", bindIp.c_str(), bindPort);

		close(sock);
		return nullptr;
	}

	temp = ttl;
	if (setsockopt(sock, IPPROTO_IP, IP_TTL, (const void *)&temp, sizeof(temp)) != 0)
	{
		int err = errno;
		LOG_WARNING("fail to set IP_TTL: %d; error was (%d) %s", ttl, err, strerror(err));
	}

	if (bind(sock, (sockaddr *)&bindAddress, sizeof(sockaddr)) != 0)
	{
		int err = errno;
		LOG_ERROR("fail to bind on address, (%d) %s", err, strerror(err));

		close(sock);

		return nullptr;
	}

	UdpCarrierHandler *udpCarrier = new (std::nothrow) UdpCarrierHandler(sock);
	if (!udpCarrier)
	{
		close(sock);

		LOG_ERROR("fail to create UdpCarrierHandler object");
	}

	return udpCarrier;
}