#include "io_utils.h"

#include <error.h>
#include <errno.h>
#include <sys/epoll.h>

bool is_epoll_supported()
{
    struct epoll_event ev;

    ev.events = EPOLLIN;
    ev.data.ptr = nullptr;
    epoll_ctl(-1, EPOLL_CTL_ADD, -1, &ev);

    return (errno != ENOSYS);
}