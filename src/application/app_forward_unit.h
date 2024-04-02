#ifndef _H_APP_FORWARD_UNIT_H_
#define _H_APP_FORWARD_UNIT_H_

#include "io_socket_buffer.h"
#include "io_udp_carrier.h"
#include "common_json.h"

/**
 * @brief The data-forward unit class
 * 
 */
class AppForwardUnit
{
public:
    AppForwardUnit(const AppForwardUnit &) = delete;
    AppForwardUnit &operator=(const AppForwardUnit &) = delete;
    AppForwardUnit(const AppForwardUnit &&) = delete;
    AppForwardUnit &operator=(const AppForwardUnit &&) = delete;

    AppForwardUnit();
    virtual ~AppForwardUnit();

    void set_recv_carrier(UdpCarrierHandler* handler);
    void set_send_carrier(UdpCarrierHandler* handler);

    bool initialize();

    /**
     * @brief the recv carrier data arrived callback
     * 
     */
    void on_recv_input();

    /**
     * @brief the send carrier data arrived callback
     * 
     */
    void on_send_input();

private:
    //the socket recv buffer
    IOSocketBuffer* m_recv_buffer = nullptr;

    //the socket send buffer
    IOSocketBuffer* m_send_buffer = nullptr;

    //the receive udp carrier
    UdpCarrierHandler* m_recv_carrier = nullptr;
    //the send udp carrier
    UdpCarrierHandler* m_send_carrier = nullptr;
};

#endif