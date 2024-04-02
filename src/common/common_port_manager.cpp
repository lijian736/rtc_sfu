#include "common_port_manager.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

PortManager::PortManager()
{
	m_initialized = false;
}

PortManager::~PortManager()
{
}

PortManager* PortManager::get_instance()
{
	static PortManager instance;
	return &instance;
}

void PortManager::initialize_udp_ports(uint16_t start, uint16_t end)
{
	m_available_ports.clear();
	m_ports_in_use.clear();

	for (uint16_t i = start; i < end; i++)
	{
		m_available_ports.push_back(i);
	}

	m_initialized = true;
}

bool PortManager::get_port(uint16_t& port, PortType type)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_available_ports.empty())
	{
		std::set<uint16_t>::const_iterator it = m_ports_in_use.begin();
		while (it != m_ports_in_use.end())
		{
			m_available_ports.push_back(*it);
			it++;
		}

		m_ports_in_use.clear();
	}

	while (!m_available_ports.empty())
	{
		std::vector<uint16_t>::const_iterator it = m_available_ports.begin();
		if (it != m_available_ports.end())
		{
			port = *it;
			
			//check if the port is available
			if (check_available(port, type))
			{
				m_ports_in_use.insert(port);
				m_available_ports.erase(it);

				return true;
			}
			else
			{
				m_ports_in_use.insert(port);
				m_available_ports.erase(it);
				continue;
			}
		}
	}

	if (m_available_ports.empty())
	{
		std::set<uint16_t>::const_iterator it = m_ports_in_use.begin();
		while (it != m_ports_in_use.end())
		{
			m_available_ports.push_back(*it);
			it++;
		}

		m_ports_in_use.clear();
	}

	return false;
}

bool PortManager::release_port(uint16_t port)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	std::set<uint16_t>::iterator it = m_ports_in_use.find(port);
	if (it != m_ports_in_use.end())
	{
		m_available_ports.push_back(port);
		m_ports_in_use.erase(it);

		return true;
	}

	return false;
}

bool PortManager::check_available(uint16_t port, PortType type)
{
	int listenSocket;
	
	listenSocket = ::socket(PF_INET, (type == PortType::PORT_TYPE_UDP) ? SOCK_DGRAM : SOCK_STREAM, (type == PortType::PORT_TYPE_UDP) ? IPPROTO_UDP : IPPROTO_TCP);
	if (listenSocket == -1)
	{
		return false;
	}

	struct sockaddr_in service;
	service.sin_family = PF_INET;
	service.sin_addr.s_addr = inet_addr("0.0.0.0");
	service.sin_port = htons(port);

	int one = 1;
	if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, (const void *)&one, sizeof(one)) != 0)
	{
		close(listenSocket);
		return false;
	}

	if (bind(listenSocket, (struct sockaddr*)&service, sizeof(service)) != 0)
	{
		close(listenSocket);
		return false;
	}

	close(listenSocket);
	return true;
}