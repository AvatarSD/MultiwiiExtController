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

class BaseStreamer : public BSerialPort
{
public:
    BaseStreamer();
    ~BaseStreamer();

    void sendCmd(char* header, // Call this method for send something
    		char* messege,
    		unsigned char headerLength,
			unsigned int messageLength);

private:
	void read(char * inData, int byteToRead); // Parse the input data then call takeCmd()

    virtual void takeCmd(char* header, // Override this method for take incoming message
    		char* message,
    		unsigned char headerLength,
			unsigned int messageLenth);
};

#endif // BASESTREAMER_H
