/*
 * ThreadTimer.cpp
 *
 *  Created on: 24 груд. 2015
 *      Author: sd
 */

#include "ThreadTimer.h"
#include "boost/bind.hpp"

ThreadTimer::ThreadTimer(uint64_t usec) :
		_io(), _timer(_io), _thread(&ThreadTimer::worker, this)
{
	setPeriod(usec);
}


ThreadTimer::~ThreadTimer()
{
	stop();

}

void ThreadTimer::setPeriod(uint64_t usec)
{
	_usec = usec;
}

void ThreadTimer::stop()
{
	_io.stop();
}

void ThreadTimer::start()
{
	_io.reset();
	_timer.async_wait(
			boost::bind(&ThreadTimer::handler, this,
					boost::asio::placeholders::error));

}

void ThreadTimer::worker()
{
	while (true)
	{
		boost::system::error_code ec;
		_io.run();
		std::cerr << ec.message() << std::endl;
	}
}

void ThreadTimer::handler(const boost::system::error_code& err)
{
	callback();
	_timer.expires_at(
			_timer.expires_at() + boost::posix_time::microseconds(_usec));
	_timer.async_wait(
			boost::bind(&ThreadTimer::handler, this,
					boost::asio::placeholders::error));
}
