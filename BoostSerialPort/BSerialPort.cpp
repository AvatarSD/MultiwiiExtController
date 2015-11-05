/*
 * BSerialPort.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: sd
 */

#include "BSerialPort.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;

BSerialPort::BSerialPort(int bufLenth)
{
	this->_buffersize = bufLenth;
	this->_dataBuffer = new char[_buffersize];
	this->_port = new serial_port(this->_service);
}

BSerialPort::~BSerialPort()
{
	disconnect();
	delete this->_dataBuffer;
	delete this->_port;

}

int BSerialPort::connect(std::string port, int baud)
{
	if(!(_port->is_open()))
	{
		_portname = port;
		try
		{
			_port->open(port);
			_port->set_option(serial_port_base::baud_rate(baud));
			_port->set_option(serial_port_base::character_size(8));
			_port->set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
			_port->set_option(serial_port_base::parity(serial_port_base::parity::none));
			_port->set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));


			_port->async_read_some(buffer(_dataBuffer, _buffersize),
					boost::bind(&BSerialPort::takeByte, this, _1, _2));
			boost::thread t(boost::bind(&BSerialPort::worker, this));
			t.detach();
			return 0;
		}
		catch (...)
		{
			return -1;
		}
	}
	return 1;
}

void BSerialPort::disconnect()
{
	if(!(_service.stopped()))
	{
		_service.reset();
		_service.stop();
	}
	if(_port->is_open())_port->close();
	_portname.clear();
}

void BSerialPort::takeByte(const boost::system::error_code& error,
		  std::size_t bytes_transferred)
{
    if (/*(boost::asio::error::eof == error) ||*/
	        (boost::asio::error::connection_reset == error))
	{
        //disconnect();
		disconnectEvent(error.message());
	  // handle the disconnect.
	}
	else
	{
        this->read(_dataBuffer, bytes_transferred);

        _port->async_read_some(buffer(_dataBuffer, _buffersize),
					boost::bind(&BSerialPort::takeByte, this, _1, _2));
	}
}

void BSerialPort::write(char * data,int byteToWrite)
{
	_port->async_write_some(buffer(data, byteToWrite),
			        boost::bind(&BSerialPort::writeComplete, this, _1, _2));
}

void BSerialPort::worker()
{
    while(true)
    {
	try
	{
	_service.run();
	}
	catch (boost::system::error_code &err)
	{
		disconnectEvent(err.message());
	}
}
}

void BSerialPort::read(const char * inData, int byteToRead)
{
	std::cout << _portname << " received " << byteToRead << " byte(s): " << inData << std::endl;
	std::memset(inData, 0, _buffersize);
}

void BSerialPort::writeComplete(const boost::system::error_code& error,
          std::size_t)
{
    if (/*(boost::asio::error::eof == error) ||*/
		        (boost::asio::error::connection_reset == error))
		{
            //disconnect();
			disconnectEvent(error.message());
		  // handle the disconnect.
		}
}

bool BSerialPort::isConnected()
{
	return this->_port->is_open();
}

void BSerialPort::disconnectEvent(std::string err)
{
	std::cout << "Error: " << err << std::endl;
}



