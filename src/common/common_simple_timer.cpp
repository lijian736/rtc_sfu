#include "common_simple_timer.h"

SimpleTimer::SimpleTimer()
	:m_expired(true), m_try_expire(false)
{
}

SimpleTimer::~SimpleTimer()
{
	cancel_timer();
}

void SimpleTimer::run_repeatedly(int interval, std::function<void()> task)
{
	if (!m_expired)
	{
		return;
	}

	m_expired = false;

	std::thread([this, interval, task]()
	{
		while (!m_try_expire)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			task();
		}
		{
			std::lock_guard<std::mutex> locker(m_mutex);
			m_expired = true;
			m_expired_cond.notify_one();
		}
	}).detach();
}

void SimpleTimer::cancel_timer()
{
	if (m_expired)
	{
		return;
	}

	if (m_try_expire)
	{
		return;
	}
	m_try_expire = true;
	{
		std::unique_lock<std::mutex> locker(m_mutex);
		m_expired_cond.wait(locker, [this] {return m_expired == true; });
		if (m_expired == true)
		{
			m_try_expire = false;
		}
	}
}