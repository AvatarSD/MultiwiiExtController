/*
 * BSerialPort.h
 *
 *  Created on: Jun 22, 2015
 *      Author: sd
 */

#ifndef BOOSTSERIALPORT_BSERIALPORT_H_
#define BOOSTSERIALPORT_BSERIALPORT_H_

//#include <QObject>
#include "boost/asio.hpp"
#include <string>


class BSerialPort
{
public:
	BSerialPort(int bufLenth = 512);
	virtual ~BSerialPort();

	int connect(std::string port, int baud = 115200);
	void disconnect();
	void write(char * data,int byteToWrite);

	bool isConnected();

protected:
	int _buffersize;
    virtual void read(const char * inData, int byteToRead);
    virtual void writeComplete(const boost::system::error_code& error, std::size_t);
    virtual void disconnectEvent(std::string err);

private:
	/* COM PORT variables */
	boost::asio::io_service _service;
	boost::asio::serial_port * _port;
	std::string _portname;
	char * _dataBuffer;
	void worker();
	void takeByte(const boost::system::error_code& error,
			      std::size_t bytes_transferred);
};

#endif /* BOOSTSERIALPORT_BSERIALPORT_H_ */
