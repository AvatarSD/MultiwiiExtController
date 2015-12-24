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

class ThreadTimer
{
public:
	ThreadTimer();

	std::function<void()> callback;

	void setPeriod();
	void stop();
	void start();

private:
	boost::asio::io_service _io;
	boost::asio::deadline_timer _t;
};

#endif /* SERVICE_TIMER_THREADTIMER_H_ */
