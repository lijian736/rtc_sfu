#ifndef _H_IO_SOCKET_HANDLER_H_
#define _H_IO_SOCKET_HANDLER_H_

#include <string>
#include <sys/epoll.h>

/**
 * @brief the base socket handler for tcp and udp
 * 
 */
class IOSocketHandler
{
public:
    IOSocketHandler() = delete;
    IOSocketHandler(const IOSocketHandler &) = delete;
    IOSocketHandler &operator=(const IOSocketHandler &) = delete;
    IOSocketHandler(const IOSocketHandler &&) = delete;
    IOSocketHandler &operator=(const IOSocketHandler &&) = delete;

    /**
     * @brief Construct a new IOSocketHandler
     * 
     * @param readFd -- the read fd
     * @param writeFd -- the write fd
     */
    IOSocketHandler(int readFd, int writeFd);
    virtual ~IOSocketHandler();

    /**
     * @brief Get the handler id
     * 
     * @return int -- handler id
     */
    int get_id();

    /**
     * @brief Get the read fd
     * 
     * @return int -- read fd
     */
    int get_read_fd();

    /**
     * @brief Get the write fd
     * 
     * @return int -- write fd
     */
    int get_write_fd();

    /**
	 * @brief enter the queue to delete
	 * 
	 */
    void enqueue_for_delete();

    /**
     * @brief notify that the handler should output data
     * 
     * @return true 
     * @return false 
     */
    virtual bool notify_output_data() = 0;

    /**
     * @brief the epoll event happens
     * 
     * @param event 
     * @return true -- event successful
     * @return false -- failed, the handler should be deleted
     */
    virtual bool on_event(struct epoll_event &event) = 0;

protected:
    //the id of the handler
    int m_id;

    //read fd
    int m_read_fd;

    //write fd
    int m_write_fd;
};

#endif