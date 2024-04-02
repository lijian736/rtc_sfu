#ifndef _H_IO_SOCKET_BUFFER_H_
#define _H_IO_SOCKET_BUFFER_H_

#include <string>
#include <list>

#include <sys/socket.h>
#include <netinet/in.h>

#include "common_address_ipv4.h"

constexpr int IO_SOCKET_BUFFER_SIZE = 1024 * 4;

constexpr int ERROR_OK = 0;
constexpr int ERROR_NO_MEMORY = 1;
constexpr int ERROR_SOCKET_ERROR = 2;
constexpr int ERROR_SOCKET_CLOSED = 3;

/**
 * @brief the Socket I/O Buffer
 * 
 */
class IOSocketBuffer
{
public:
    IOSocketBuffer(const IOSocketBuffer &) = delete;
    IOSocketBuffer &operator=(const IOSocketBuffer &) = delete;
    IOSocketBuffer(const IOSocketBuffer &&) = delete;
    IOSocketBuffer &operator=(const IOSocketBuffer &&) = delete;

    IOSocketBuffer();
    virtual ~IOSocketBuffer();

    /**
     * @brief read from the tcp file descriptor.
     * 
     * @param fd -- file descriptor
     * @param read_length -- out parameter. the actually read length
     * @return int - error code
     */
    int read_tcp_fd(int fd, int *read_length);

    /**
     * @brief read from the udp file descriptor.
     * 
     * @param fd  -- file descriptor
     * @param read_length -- out parameter. the actually read length
     * @param peer_address -- out parameter. the peer address
     * @return int -- error code
     */
    int read_udp_fd(int fd, int *read_length, struct sockaddr_in *peer_address);

    /**
     * @brief read from the string
     * 
     * @param str -- string 
     * @return int -- error code
     */
    int read_from_string(const std::string &str);

    /**
     * @brief read from buffer
     * 
     * @param bytes -- the bytes
     * @param len -- the length of bytes
     * @return int -- error code
     */
    int read_from_buffer(char *bytes, int len);

    /**
     * @brief write all to the tcp file descriptor.
     * 
     * @param fd -- file descriptor
     * @param sent_length -- out parameter. the actually sent length
     * @return int -- error code
     */
    int write_all_tcp_fd(int fd, int *sent_length);

    /**
     * @brief write all to the udp file descriptor.
     * 
     * @param fd -- file descriptor
     * @param sent_length -- out parameter. the actually sent length
     * @param peer_address -- the peer socket address
     * @return int -- error code
     */
    int write_all_udp_fd(int fd, int *sent_length, struct sockaddr_in *peer_address);

    /**
     * @brief write all to the udp file descriptor. the destination is in peer_address
     * 
     * @param fd -- file descriptor
     * @param peer_addresses -- the peer socket address list
     * @return int -- error code
     */
    int write_all_udp_fd(int fd, std::list<IPAddrV4*>& peer_address);

    /**
     * @brief Get the buffer data pointer
     * 
     * @return char*, the buffer data pointer
     */
    char *get_data() const;

    /**
     * @brief Get the buffer data length
     * 
     * @return int, the buffer data length
     */
    int get_used_length() const;

    /**
     * @brief reset
     * 
     */
    void reset();

    /**
     * @brief reset the len space. the following space will move forward
     * 
     * @param len 
     */
    void reset_length(int len);

private:
    //buffer
    char m_buffer[IO_SOCKET_BUFFER_SIZE];

    //the used length
    int m_used_len;
};

#endif