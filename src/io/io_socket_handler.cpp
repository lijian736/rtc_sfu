#include "io_socket_handler.h"

#include <atomic>
#include <string.h>

#include "io_socket_handler_mgr.h"

namespace
{
    std::atomic<int> g_id_generator(1);
}

IOSocketHandler::IOSocketHandler(int readFd, int writeFd)
    : m_read_fd(readFd), m_write_fd(writeFd)
{
    m_id = ++g_id_generator;

    //add this to the handler manager
    IOSocketHandlerMgr::add_handler(this);
}

IOSocketHandler::~IOSocketHandler()
{
    //remove this from the handler manager
    IOSocketHandlerMgr::remove_handler(this);
}

int IOSocketHandler::get_id()
{
    return this->m_id;
}

int IOSocketHandler::get_read_fd()
{
    return this->m_read_fd;
}

int IOSocketHandler::get_write_fd()
{
    return this->m_write_fd;
}

void IOSocketHandler::enqueue_for_delete()
{
    IOSocketHandlerMgr::enqueue_for_delete(this);
}