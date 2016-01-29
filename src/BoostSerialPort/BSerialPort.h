/*
 * BSerialPort.h
 *
 *  Created on: Jun 22, 2015
 *      Author: sd
 */

#ifndef BOOSTSERIALPORT_BSERIALPORT_H_
#define BOOSTSERIALPORT_BSERIALPORT_H_

#include "boost/asio.hpp"
#include <string>
#include "../stream/AsyncIOStream.h"


class BSerialPort : public AsyncIOStream
{
public:
	BSerialPort(int bufLenth = 512);
	virtual ~BSerialPort();

	int connect(std::string port, int baud = 115200);
	void disconnect();

	bool isConnected();

/* todo make as functional */
	virtual void writeComplete(const boost::system::error_code& error,
			std::size_t);
	virtual void disconnectEvent(std::string err);

private:
	/* COM PORT variables */
	boost::asio::io_service _service;
	boost::asio::serial_port * _port;
	std::string _portname;
	uint8_t * _dataBuffer;
	int _buffersize;
	void worker();
	void takeByte(const boost::system::error_code& error,
			std::size_t bytes_transferred);
	void write(char * data,int byteToWrite);
};

#endif /* BOOSTSERIALPORT_BSERIALPORT_H_ */
