#ifndef _H_IO_UDP_CARRIER_H_
#define _H_IO_UDP_CARRIER_H_

#include <string>
#include <list>
#include <mutex>
#include <functional>

#include <stdint.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "common_address_ipv4.h"
#include "io_socket_handler.h"
#include "io_socket_buffer.h"

/**
 * @brief the socket data arrived callback function
 * 
 */
typedef std::function<void()> DataInputCallback; 

/**
 * @brief The UDP carrier handler
 * 
 */
class UdpCarrierHandler : public IOSocketHandler
{
protected:
    UdpCarrierHandler(int fd);

public:
    UdpCarrierHandler() = delete;
    UdpCarrierHandler(const UdpCarrierHandler &) = delete;
    UdpCarrierHandler &operator=(const UdpCarrierHandler &) = delete;
    UdpCarrierHandler(const UdpCarrierHandler &&) = delete;
    UdpCarrierHandler &operator=(const UdpCarrierHandler &&) = delete;

    virtual ~UdpCarrierHandler();

    virtual bool notify_output_data() override;
    virtual bool on_event(struct epoll_event &event) override;

    /**
     * @brief Set the recv buffer object
     * 
     * @param buffer 
     */
    void set_recv_buffer(IOSocketBuffer* buffer);

    /**
     * @brief Set the send buffer object
     * 
     * @param buffer 
     */
    void set_send_buffer(IOSocketBuffer* buffer);

    /**
     * @brief Set the data input callback function
     * 
     * @param func -- the callback function
     */
    void set_data_input_callback(DataInputCallback func);

    /**
     * @brief Start the UDP carrier
     * 
     * @return true 
     * @return false 
     */
    bool start();

    /**
     * @brief Get the peer address 
     * 
     * @return struct sockaddr_in* 
     */
    struct sockaddr_in* get_peer_address();

    /**
     * @brief add destination
     * 
     * @param ip -- the destination ip
     * @param port -- the destination port
     * @return true -- add successfully
     * @return false -- failed
     */
    bool add_destination(const std::string &ip, const uint16_t& port);

    /**
     * @brief remove destination
     * 
     * @param ip -- the destination ip
     * @param port -- the destination port
     * @return true -- remove successfully
     * @return false -- failed
     */
    bool remove_destination(const std::string& ip, const uint16_t& port);

    static UdpCarrierHandler *create(std::string bindIp, uint16_t bindPort, uint16_t ttl,
                                     uint16_t tos);

private:
    bool read_data();
    bool write_data();

private:
    //the peer address
    struct sockaddr_in m_peer_address;
    socklen_t m_sock_len;

    //the mutex for destination list
    std::mutex m_mutex;
    //the destination list
    std::list<IPAddrV4 *> m_destination_list;

    //the socket recv data buffer
    IOSocketBuffer* m_recv_buffer = nullptr;

    //the socket send data buffer
    IOSocketBuffer* m_send_buffer = nullptr;

    //the data input callback
    DataInputCallback m_data_input_callback = nullptr;
};

#endif