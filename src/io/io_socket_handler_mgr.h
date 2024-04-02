#ifndef _H_IO_SOCKET_HANDLER_MANAGER_H_
#define _H_IO_SOCKET_HANDLER_MANAGER_H_

#include <map>
#include <sys/epoll.h>

constexpr int MAX_EVENTS_NUM = 512;

class IOSocketHandler;

/**
 * @brief the io socket handler manager
 * 
 */
class IOSocketHandlerMgr
{
public:
	IOSocketHandlerMgr() = delete;
	IOSocketHandlerMgr(const IOSocketHandlerMgr &) = delete;
	IOSocketHandlerMgr &operator=(const IOSocketHandlerMgr &) = delete;
	IOSocketHandlerMgr(const IOSocketHandlerMgr &&) = delete;
	IOSocketHandlerMgr &operator=(const IOSocketHandlerMgr &&) = delete;

	/**
	 * @brief init the manager
	 * 
	 * @return true 
	 * @return false 
	 */
	static bool init();

	/**
	 * @brief shutdown the manager
	 * 
	 * @return true 
	 * @return false 
	 */
	static bool shutdown();

	/**
	 * @brief close all the handlers.
	 * the function delete_inactive_handlers() should invoked after
	 * this function close_all_iohandlers invoked.
	 */
	static void close_all_iohandlers();

	/**
	 * @brief add the handler to the manager
	 * 
	 * @param handler 
	 */
	static void add_handler(IOSocketHandler *handler);

	/**
	 * @brief remove the handler from the manager
	 * 
	 * @param handler 
	 */
	static void remove_handler(IOSocketHandler *handler);

	static bool enable_read_data(IOSocketHandler *handler);
	static bool disable_read_data(IOSocketHandler *handler);
	static bool enable_write_data(IOSocketHandler *handler);
	static bool disable_write_data(IOSocketHandler *handler);
	static bool enable_accept_connections(IOSocketHandler *handler);
	static bool disable_accept_connections(IOSocketHandler *handler);

	/**
	 * @brief the handler should deleted. 
	 * when delete_inactive_handlers() invoked, 
	 * the handler is actually deleted.
	 * 
	 * @param handler -- the handler
	 */
	static void enqueue_for_delete(IOSocketHandler *handler);

	/**
	 * @brief delete the inactive handlers.
	 * 
	 * @return int -- delete handlers count
	 */
	static int delete_inactive_handlers();

	/**
	 * @brief the cycle loop
	 * 
	 * @return true
	 * @return false
	 */
	static bool cycle();

private:
	static struct epoll_event m_events[MAX_EVENTS_NUM];
	//the epoll fd
	static int m_epoll_fd;

	//key: handler id, value:handler ptr
	static std::map<int, IOSocketHandler *> m_active_handlers;
	static std::map<int, IOSocketHandler *> m_inactive_handlers;
};

#endif