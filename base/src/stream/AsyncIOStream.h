/*
 * Stream.h
 *
 *  Created on: 29 січ. 2016
 *      Author: sd
 */

#ifndef STREAM_ASYNCIOSTREAM_H_
#define STREAM_ASYNCIOSTREAM_H_

#include <functional>

class AsyncIOStream
{
public:
	AsyncIOStream();
	virtual ~AsyncIOStream();

	virtual void write(const uint8_t * data, uint32_t byteToWrite);
	std::function<void(const uint8_t *, uint32_t)> read;

};

#endif /* STREAM_ASYNCIOSTREAM_H_ */
