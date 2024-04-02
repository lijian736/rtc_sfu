#include "app_forward_unit.h"

AppForwardUnit::AppForwardUnit()
{
    m_recv_buffer = new (std::nothrow) IOSocketBuffer();
    m_send_buffer = new (std::nothrow) IOSocketBuffer();
}

AppForwardUnit::~AppForwardUnit()
{
    if(m_recv_buffer)
    {
        delete m_recv_buffer;
        m_recv_buffer = nullptr;
    }

    if(m_send_buffer)
    {
        delete m_send_buffer;
        m_send_buffer = nullptr;
    }
}

bool AppForwardUnit::initialize()
{
    return true;
}

void AppForwardUnit::set_recv_carrier(UdpCarrierHandler* handler)
{
    this->m_recv_carrier = handler;
    this->m_recv_carrier->set_recv_buffer(m_recv_buffer);
    this->m_recv_carrier->set_send_buffer(m_recv_buffer);
    this->m_recv_carrier->set_data_input_callback(std::bind(&AppForwardUnit::on_recv_input, this));
}

void AppForwardUnit::set_send_carrier(UdpCarrierHandler* handler)
{
    this->m_send_carrier = handler;
    this->m_send_carrier->set_recv_buffer(m_send_buffer);
    this->m_send_carrier->set_send_buffer(m_recv_buffer);
    this->m_send_carrier->set_data_input_callback(std::bind(&AppForwardUnit::on_send_input, this));
}

void AppForwardUnit::on_recv_input()
{
    (void)this->m_send_carrier->notify_output_data();
}

void AppForwardUnit::on_send_input()
{
    char* data = m_send_buffer->get_data();
    int len = m_send_buffer->get_used_length();

    JsonObject json;
    if(json.read_from_string(std::string(data, len)))
    {
        std::string opcode = json["opcode"].as_string();
        std::string userID = json["params"].as_object()["user_id"].as_string();
    }
}