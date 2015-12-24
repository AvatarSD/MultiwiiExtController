/*
 * ThreadTimer.cpp
 *
 *  Created on: 24 груд. 2015
 *      Author: sd
 */

#include "ThreadTimer.h"

ThreadTimer::ThreadTimer(uint64_t usec)
{
	_timer(_io);
	setPeriod(usec);
}

void ThreadTimer::setPeriod(uint64_t usec) : _usec(usec)
{
}

void ThreadTimer::stop()
{
	_io.stop();
}

void ThreadTimer::start()
{
	_io.reset();
	_timer.async_wait(boost::bind(&ThreadTimer::handler, this, boost::asio::placeholders::error));
	_thread(std::bind(&ThreadTimer::worker(), this));
}

void ThreadTimer::worker()
{
	_io.run();
}

void ThreadTimer::handler(const boost::system::error_code& err)
{
	callback();
	_timer.expires_at(_timer.expires_at() + boost::posix_time::microseconds(_usec));
	_timer.async_wait(boost::bind(&ThreadTimer::handler, this, boost::asio::placeholders::error));
}
