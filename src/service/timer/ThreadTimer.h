/*
 * ThreadTimer.h
 *
 *  Created on: 24 груд. 2015
 *      Author: sd
 */

#ifndef SERVICE_TIMER_THREADTIMER_H_
#define SERVICE_TIMER_THREADTIMER_H_

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <functional>
#include <thread>

class ThreadTimer
{
public:
	ThreadTimer(uint64_t usec);
	~ThreadTimer();

	std::function<void()> callback;

	void setPeriod(uint64_t usec);
	void stop();
	void start();

private:
	boost::asio::io_service _io;
	boost::asio::deadline_timer _timer;
	std::thread _thread;

	uint64_t _usec;

	void worker();
	void handler(const boost::system::error_code& err);
};

#endif /* SERVICE_TIMER_THREADTIMER_H_ */
