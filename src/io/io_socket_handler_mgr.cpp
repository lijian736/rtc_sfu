#include "io_socket_handler_mgr.h"

#include <thread>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "common_logger.h"
#include "io_socket_handler.h"

//initialize
int IOSocketHandlerMgr::m_epoll_fd = -1;
std::map<int, IOSocketHandler *> IOSocketHandlerMgr::m_active_handlers;
std::map<int, IOSocketHandler *> IOSocketHandlerMgr::m_inactive_handlers;
struct epoll_event IOSocketHandlerMgr::m_events[MAX_EVENTS_NUM];

bool IOSocketHandlerMgr::init()
{
    m_epoll_fd = epoll_create(MAX_EVENTS_NUM * 2);
    if (m_epoll_fd == -1)
    {
        int err = errno;
        LOG_ERROR("epoll_create failed: (%d) %s", err, strerror(err));
        return false;
    }

    return true;
}

bool IOSocketHandlerMgr::shutdown()
{
    if (m_epoll_fd >= 0)
    {
        close(m_epoll_fd);
        m_epoll_fd = -1;
    }

    return true;
}

void IOSocketHandlerMgr::close_all_iohandlers()
{
    std::map<int, IOSocketHandler *>::iterator it;

    for (it = m_active_handlers.begin(); it != m_active_handlers.end(); it++)
    {
        IOSocketHandlerMgr::enqueue_for_delete(it->second);
    }
}

void IOSocketHandlerMgr::add_handler(IOSocketHandler *handler)
{
    std::map<int, IOSocketHandler *>::iterator it = m_active_handlers.find(handler->get_id());
    if (it == m_active_handlers.end())
    {
        m_active_handlers[handler->get_id()] = handler;
    }
}

void IOSocketHandlerMgr::remove_handler(IOSocketHandler *handler)
{
    std::map<int, IOSocketHandler *>::iterator it = m_active_handlers.find(handler->get_id());
    if (it != m_active_handlers.end())
    {
        m_active_handlers.erase(handler->get_id());
    }
}

bool IOSocketHandlerMgr::enable_read_data(IOSocketHandler *handler)
{
    struct epoll_event evt = {0, {0}};
    evt.events = EPOLLIN; // | EPOLLET;
    evt.data.ptr = handler;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, handler->get_read_fd(), &evt) != 0)
    {
        int err = errno;
        LOG_ERROR("fail to eanble socket read: (%d) %s", err, strerror(err));

        return false;
    }

    return true;
}

bool IOSocketHandlerMgr::disable_read_data(IOSocketHandler *handler)
{
    struct epoll_event evt = {0, {0}};
    evt.events = EPOLLIN; // | EPOLLET;
    evt.data.ptr = handler;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, handler->get_read_fd(), &evt) != 0)
    {
        int err = errno;
        LOG_ERROR("fail to disable read data: (%d) %s", err, strerror(err));
        return false;
    }

    return true;
}

bool IOSocketHandlerMgr::enable_write_data(IOSocketHandler *handler)
{
    struct epoll_event evt = {0, {0}};
    evt.events = EPOLLIN | EPOLLOUT; // | EPOLLET;
    evt.data.ptr = handler;

    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, handler->get_write_fd(), &evt) != 0)
    {
        int err = errno;

        //No such file or directory
        if (err == ENOENT)
        {
            if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, handler->get_write_fd(), &evt) != 0)
            {
                err = errno;
                LOG_ERROR("fail to enable write data: (%d) %s", err, strerror(err));
                return false;
            }
        }
        else
        {
            LOG_ERROR("fail to enable write data: (%d) %s", err, strerror(err));
            return false;
        }
    }

    return true;
}

bool IOSocketHandlerMgr::disable_write_data(IOSocketHandler *handler)
{
    struct epoll_event evt = {0, {0}};
    evt.events = EPOLLIN; // | EPOLLET;
    evt.data.ptr = handler;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, handler->get_write_fd(), &evt) != 0)
    {
        int err = errno;
        LOG_ERROR("Unable to disable write data: (%d) %s", err, strerror(err));
        return false;
    }

    return true;
}

bool IOSocketHandlerMgr::enable_accept_connections(IOSocketHandler *handler)
{
    struct epoll_event evt = {0, {0}};
    evt.events = EPOLLIN; // | EPOLLET;
    evt.data.ptr = handler;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, handler->get_read_fd(), &evt) != 0)
    {
        int err = errno;

        // File exists
        if (err == EEXIST)
        {
            return true;
        }

        LOG_ERROR("fail to enable accept connections: (%d) %s", err, strerror(err));
        return false;
    }

    return true;
}

bool IOSocketHandlerMgr::disable_accept_connections(IOSocketHandler *handler)
{
    struct epoll_event evt = {0, {0}};
    evt.events = EPOLLIN; // | EPOLLET;
    evt.data.ptr = handler;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, handler->get_read_fd(), &evt) != 0)
    {
        int err = errno;
        LOG_ERROR("fail to disable accept connections: (%d) %s", err, strerror(err));
        return false;
    }

    return true;
}

void IOSocketHandlerMgr::enqueue_for_delete(IOSocketHandler *handler)
{
    struct epoll_event evt = {0, {0}};
    evt.events = EPOLLIN; // | EPOLLET;
    evt.data.ptr = handler;

    if (handler->get_write_fd() != handler->get_read_fd())
    {
        //disable write
        epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, handler->get_write_fd(), &evt);
    }

    //disable accept/read
    epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, handler->get_read_fd(), &evt);

    std::map<int, IOSocketHandler *>::iterator it = m_inactive_handlers.find(handler->get_id());
    if (it == m_inactive_handlers.end())
    {
        m_inactive_handlers[handler->get_id()] = handler;
    }
}

int IOSocketHandlerMgr::delete_inactive_handlers()
{
    int count = 0;
    while (m_inactive_handlers.size() > 0)
    {
        IOSocketHandler *handler = m_inactive_handlers.begin()->second;
        m_inactive_handlers.erase(handler->get_id());

        //delete the handler, and the handler deconstructor will invoke
        //remove_handler()
        delete handler;
        count++;
    }

    return count;
}

bool IOSocketHandlerMgr::cycle()
{
    int eventsCount = epoll_wait(m_epoll_fd, m_events, MAX_EVENTS_NUM, 1000);

    if (eventsCount < 0)
    {
        int err = errno;

        //Interrupted system call
        if (err == EINTR)
        {
            return true;
        }

        LOG_ERROR("epoll_wait failed: (%d) %s", err, strerror(err));
        return false;
    }

    for (int i = 0; i < eventsCount; i++)
    {
        IOSocketHandler *handler = (IOSocketHandler *)m_events[i].data.ptr;

        //error condition happened
        if ((m_events[i].events & EPOLLERR) != 0)
        {
            if (handler)
            {
                // the connection is closed.
                if ((m_events[i].events & EPOLLHUP) != 0)
                {
                    handler->on_event(m_events[i]);
                }

                IOSocketHandlerMgr::enqueue_for_delete(handler);
            }
            continue;
        }

        if (handler)
        {
            if (!handler->on_event(m_events[i]))
            {
                IOSocketHandlerMgr::enqueue_for_delete(handler);
            }
        }
    }

    return true;
}