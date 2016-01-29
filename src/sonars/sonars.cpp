#include "sonars.h"

#include "iostream"

#define $Byte '$'
#define $ByteNum 0
#define firstByteNameNum 1
#define secondByteNameNum 2
#define thirdByteNameNum 3
#define LBSdataByteNum 4
#define MBSdataByteNum 5
#define ChecksumByteNum 6


Sonars::Sonars(AsyncIOStream & iface) : _iface(iface)
{
	using namespace std::placeholders;
	_iface.read = std::bind(&Sonars::read, this, _1, _2);
}

void Sonars::read(const uint8_t * inData, uint32_t byteToRead)
{
    /*outputs*/
    static uint8_t outReadingByte = 0;
    static char portName[4];
    static uint16_t distance;
    static uint8_t portNum;
    static uint8_t CalcCRC = 0;

    for(uint32_t inputReadingByte = 0; inputReadingByte<byteToRead; inputReadingByte++)
    {
        //if(outReadingByte==0) memset(joydata, 0, sizeof(JoyData));

        //detect some inportant for us data(number bytes in arrived command)
        switch (outReadingByte)
        {
        case $ByteNum:
            if(inData[inputReadingByte] != $Byte) outReadingByte = 0; else
            {
                CalcCRC ^= $Byte;
                outReadingByte++;
            }
            break;

        case firstByteNameNum:
            portName[0] = inData[inputReadingByte];
            CalcCRC ^= inData[inputReadingByte];
            outReadingByte++;
            break;

        case secondByteNameNum:
            portName[1] = inData[inputReadingByte];
            portName[2] = '\0';
            CalcCRC ^= inData[inputReadingByte];
            outReadingByte++;
            break;

        case thirdByteNameNum:
            portNum = inData[inputReadingByte];
            CalcCRC ^= inData[inputReadingByte];
            outReadingByte++;
            break;

        case LBSdataByteNum:
            distance = inData[inputReadingByte];
            CalcCRC ^= inData[inputReadingByte];
            outReadingByte++;
            break;

        case MBSdataByteNum:
            distance |= inData[inputReadingByte] << 8;
            CalcCRC ^= inData[inputReadingByte];
            outReadingByte++;
            break;

        case ChecksumByteNum:
            unsigned char CmdCRC = inData[inputReadingByte];
            if(CalcCRC == CmdCRC)
                dataResived(SonarData(portName, portNum, distance));
            outReadingByte = 0;
            CalcCRC = 0;
            break;

        }
    }
}

