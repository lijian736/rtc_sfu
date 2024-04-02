#ifndef _H_COMMON_SIMPLE_TIMER_H_
#define _H_COMMON_SIMPLE_TIMER_H_

#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>

/**
 * @brief the simple timer
 * 
 */
class SimpleTimer
{
public:
	SimpleTimer();
	~SimpleTimer();

	/**
	 * @brief run repeatedly after interval milliseconds
	 * @param interval -- the interval in milliseconds
	 * @param task -- the function to run
	 */
	void run_repeatedly(int interval, std::function<void()> task);

	/**
	 * @brief run once synchronized after delay milliseconds
	 * @param delay -- delay in milliseconds
	 * @param fun -- the function to run
	 * @param args -- the parameters of the function
	 *
	 */
	template<typename callback, class... arguments>
	void run_once_sync(int delay, callback&& fun, arguments&&... args)
	{
		std::function<typename std::result_of<callback(arguments...)>::type()> task
			(std::bind(std::forward<callback>(fun), std::forward<arguments>(args)...));
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		task();
	}

	/**
	 * @brief run once asynchronized after delay milliseconds
	 * @param delay -- delay in milliseconds
	 * @param fun -- the function to run
	 * @param args -- the parameters of the function
	 *
	 */
	template<typename callback, class... arguments>
	void run_once_async(int delay, callback&& fun, arguments&&... args)
	{
		std::function<typename std::result_of<callback(arguments...)>::type()> task
			(std::bind(std::forward<callback>(fun), std::forward<arguments>(args)...));

		std::thread([delay, task]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			task();
		}).detach();
	}

	/**
	 * @brief cancel the timer
	 */
	void cancel_timer();

private:
	//is the timer expired?
	std::atomic<bool> m_expired;
	//try to expire
	std::atomic<bool> m_try_expire;
	std::mutex m_mutex;
	std::condition_variable m_expired_cond;
};

#endif