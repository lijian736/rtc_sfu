#include "io_socket_buffer.h"

#include <string.h>
#include <errno.h>

#include "common_logger.h"

IOSocketBuffer::IOSocketBuffer()
    : m_used_len(0)
{
    memset(m_buffer, 0, IO_SOCKET_BUFFER_SIZE);
}

IOSocketBuffer::~IOSocketBuffer()
{
}

int IOSocketBuffer::read_tcp_fd(int fd, int *read_length)
{
    //no memory for read
    if (IO_SOCKET_BUFFER_SIZE - m_used_len <= 1)
    {
        return ERROR_NO_MEMORY;
    }

    int read_count = recv(fd, m_buffer + m_used_len, IO_SOCKET_BUFFER_SIZE - m_used_len, MSG_DONTWAIT);
    if (read_count == -1)
    {
        int err = errno;
        LOG_ERROR("read tcp fd fail. (%d) %s", err, strerror(err));

        return ERROR_SOCKET_ERROR;
    }
    else if (read_count == 0)
    {
        LOG_INFO("tcp client connection closed");

        return ERROR_SOCKET_CLOSED;
    }
    else
    {
        m_used_len += read_count;
    }

    if (read_length)
    {
        *read_length = read_count;
    }

    return ERROR_OK;
}

int IOSocketBuffer::read_udp_fd(int fd, int *read_length, struct sockaddr_in *peer_address)
{
    socklen_t sock_len = sizeof(sockaddr_in);
    if (!peer_address)
    {
        sock_len = 0;
    }

    //no memory for read
    if (IO_SOCKET_BUFFER_SIZE - m_used_len <= 1)
    {
        return ERROR_NO_MEMORY;
    }

    int read_count = recvfrom(fd, m_buffer + m_used_len, IO_SOCKET_BUFFER_SIZE - m_used_len, MSG_DONTWAIT, (struct sockaddr *)peer_address, &sock_len);
    if (read_count == -1)
    {
        int err = errno;

        LOG_ERROR("fail to read udp data. (%d) %s", err, strerror(err));
        return ERROR_SOCKET_ERROR;
    }
    else if (read_count == 0)
    {
        // Datagram sockets in various domains (e.g., the UNIX and Internet
        // domains) permit zero-length datagrams.  When such a datagram is
        // received, the return value is 0
        if (read_length)
        {
            *read_length = 0;
        }
        return ERROR_OK;
    }
    else
    {
        m_used_len += read_count;
    }

    if (read_length)
    {
        *read_length = read_count;
    }

    return ERROR_OK;
}

int IOSocketBuffer::read_from_string(const std::string &str)
{
    int length = (int)str.length();
    if (length <= IO_SOCKET_BUFFER_SIZE - m_used_len)
    {
        memcpy(m_buffer + m_used_len, str.data(), length);
        m_used_len += length;

        return ERROR_OK;
    }
    else
    {
        return ERROR_NO_MEMORY;
    }
}

int IOSocketBuffer::read_from_buffer(char *bytes, int length)
{
    if (length <= IO_SOCKET_BUFFER_SIZE - m_used_len)
    {
        memcpy(m_buffer + m_used_len, bytes, length);
        m_used_len += length;

        return ERROR_OK;
    }
    else
    {
        return ERROR_NO_MEMORY;
    }
}

int IOSocketBuffer::write_all_tcp_fd(int fd, int *sent_length)
{
    int write_count = 0;
    int write_total = 0;

    while (write_total < m_used_len)
    {
        write_count = send(fd, m_buffer + write_total, m_used_len - write_total, MSG_DONTWAIT);
        if (write_count >= 0)
        {
            write_total += write_count;
        }
        else if (write_count == -1)
        {
            int err = errno;
            LOG_ERROR("write tcp data fail. (%d) %s", err, strerror(err));

            return ERROR_SOCKET_ERROR;
        }
    }

    if (sent_length)
    {
        *sent_length = write_total;
    }

    m_used_len = 0;
    return ERROR_OK;
}

int IOSocketBuffer::write_all_udp_fd(int fd, int *sent_length, struct sockaddr_in *peer_address)
{
    socklen_t sock_len = sizeof(sockaddr_in);
    if (!peer_address)
    {
        return ERROR_SOCKET_ERROR;
    }

    int write_count = 0;
    int write_total = 0;

    while (write_total < m_used_len)
    {
        write_count = sendto(fd, m_buffer + write_total, m_used_len - write_total, MSG_DONTWAIT, (struct sockaddr *)peer_address, sock_len);
        if (write_count >= 0)
        {
            write_total += write_count;
        }
        else if (write_count == -1)
        {
            int err = errno;
            LOG_ERROR("write udp data fail. (%d) %s", err, strerror(err));

            return ERROR_SOCKET_ERROR;
        }
    }

    if (sent_length)
    {
        *sent_length = write_total;
    }

    m_used_len = 0;
    return ERROR_OK;
}

int IOSocketBuffer::write_all_udp_fd(int fd, std::list<IPAddrV4 *> &destination_list)
{
    socklen_t sock_len = sizeof(sockaddr_in);

    int write_count = 0;
    int write_total = 0;

    std::list<IPAddrV4 *>::iterator it;
    for (it = destination_list.begin(); it != destination_list.end(); it++)
    {
        write_count = 0;
        write_total = 0;

        while (write_total < m_used_len)
        {
            write_count = sendto(fd, m_buffer + write_total, m_used_len - write_total, MSG_DONTWAIT, (struct sockaddr *)(*it)->get_sock_addr(), sock_len);
            if (write_count >= 0)
            {
                write_total += write_count;
            }
            else if (write_count == -1)
            {
                int err = errno;
                LOG_ERROR("write udp data fail. (%d) %s", err, strerror(err));

                break;
            }
        }
    }

    m_used_len = 0;
    return ERROR_OK;
}

char *IOSocketBuffer::get_data() const
{
    return (char *)this->m_buffer;
}

int IOSocketBuffer::get_used_length() const
{
    return this->m_used_len;
}

void IOSocketBuffer::reset()
{
    this->m_used_len = 0;
}

void IOSocketBuffer::reset_length(int len)
{
    if (len >= m_used_len)
    {
        m_used_len = 0;
        return;
    }

    memmove(m_buffer, m_buffer + len, m_used_len - len);

    m_used_len -= len;
}