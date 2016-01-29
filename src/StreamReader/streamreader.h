/*
 * Simple message streamer and parser
 * by S.D.
 * Copter project
 *
 * Message signature is:
 * [startByte][headerLenth][messegeLenth][header][message]
 * where:
 * startByte - first message signature;
 * headerLenth - header length. One byte, unsigned char
 * messegeLenth
 * header
 * message
 */

#ifndef BASESTREAMER_H
#define BASESTREAMER_H

#include "../BoostSerialPort/BSerialPort.h"

#define startBytes      "$SD" // First message signature

struct Message
{
	Message(const uint8_t * Header,
			const uint8_t * Data,
			uint8_t HeaderLength,
			uint32_t DataLength) :
			header(Header), data(Data),
			headerLength(HeaderLength), dataLength(DataLength)
	{
	}

	const uint8_t * header;
	const uint8_t * data;
	const uint8_t headerLength;
	const uint32_t dataLength;
};

class StreamReader: public BSerialPort
{
public:
	StreamReader();
	~StreamReader();

	// Call this method for send something
	void sendCmd(const Message & message);
	std::function<void(const Message & message)> takeCmd;

private:
	void read(char * inData, int byteToRead); // Parse the input data then call takeCmd()
	//BSerialPort & _iface;
};

#endif // BASESTREAMER_H

