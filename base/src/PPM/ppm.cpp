#include "ppm.h"

#include <iostream>

#define $Byte '$'
#define $ByteNum 0

#define RByte 'R'
#define RByteNum 1

#define CByte 'C'
#define CByteNum 2

#define NumByteNum 3

#define LBSdataByteNum 4
#define MBSdataByteNum 5

#define ChecksumByteNum 6

PPM::PPM(AsyncIOStream & iface) :
		_iface(iface)
{
	using namespace std::placeholders;
	_iface.read = std::bind(&PPM::read, this, _1, _2);
}

void PPM::read(const uint8_t * inData, uint32_t byteToRead)
{
	/*outputs*/
	static uint8_t outReadingByte = 0;
	static uint16_t rcData;
	static uint8_t portNum;
	static uint8_t CalcCRC = 0;

	for (uint32_t inputReadingByte = 0; inputReadingByte < byteToRead;
			inputReadingByte++)
	{
		//if(outReadingByte==0) memset(joydata, 0, sizeof(JoyData));

		//detect some inportant for us data(number bytes in arrived command)
		switch (outReadingByte)
		{
		case $ByteNum:
			if (inData[inputReadingByte] != $Byte)
				outReadingByte = 0;
			else
			{
				rcData = 0;
				CalcCRC ^= $Byte;
				outReadingByte++;
			}
			break;

		case RByteNum:
			if (inData[inputReadingByte] != RByte)
				outReadingByte = 0;
			else
			{
				CalcCRC ^= RByte;
				outReadingByte++;
			}
			break;

		case CByteNum:
			if (inData[inputReadingByte] != CByte)
				outReadingByte = 0;
			else
			{
				CalcCRC ^= CByte;
				outReadingByte++;
			}
			break;

		case NumByteNum:
			portNum = inData[inputReadingByte];
			CalcCRC ^= inData[inputReadingByte];
			outReadingByte++;
			break;

		case LBSdataByteNum:
			rcData = inData[inputReadingByte];
			CalcCRC ^= inData[inputReadingByte];
			outReadingByte++;
			break;

		case MBSdataByteNum:
			rcData |= inData[inputReadingByte] << 8;
			CalcCRC ^= inData[inputReadingByte];
			outReadingByte++;
			break;

		case ChecksumByteNum:
			unsigned char CmdCRC = inData[inputReadingByte];
			if (CalcCRC == CmdCRC)
			{
				_rcTemp(portNum, rcData);
				if (rawDataResived)
					rawDataResived(_rcTemp);
				dataParse(_rcTemp);
			}
			outReadingByte = 0;
			CalcCRC = 0;
			break;

		}
	}
}

void PPM::dataParse(const RC & data)
{
	if (data.channel() == 0)
	{
		if (!_additional.empty())
			if (additionalData)
				additionalData(_additional);
		_control.clear();
		_additional.clear();
	}

	if (data.channel() <= 3)
		_control.push_back(data);

	if (data.channel() == 3)
		controlData(_control);

	if (data.channel() >= 4)
		_additional.push_back(data);
}

/********************/
RC::RC()
{
	_channel = 0;
	_value = 1500;
}

RC::RC(uint8_t channel, uint16_t value) :
		_channel(channel), _value(value)
{

}

uint8_t RC::channel() const
{
	return _channel;
}

void RC::setChannel(const uint8_t &channel)
{
	_channel = channel;
}
uint16_t RC::value() const
{
	return _value;
}

void RC::setValue(const uint16_t &value)
{
	_value = value;
}

void *RC::operator ()(uint8_t channel, uint16_t value)
{
	_channel = channel;
	_value = value;
	return 0;
}

