#include "sonars.h"

#include "iostream"

#define $Byte '$'
//#define PByte 'P'
#define $ByteNum 0
#define PByteNum 1
#define LBSportByteNum 2
#define MBSportByteNum 3
#define LBSdataByteNum 4
#define MBSdataByteNum 5
#define ChecksumByteNum 6


Sonars::Sonars()
{

}

void Sonars::read(const uint8_t *inData, int byteToRead)
{


    /*outputs*/
    static uint8_t outReadingByte = 0;
    static char portName[4];
    static uint16_t distance;
    static uint8_t portNum;
    static uint8_t CalcCRC = 0;

    for(int inputReadingByte = 0; inputReadingByte<byteToRead; inputReadingByte++)
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

        case PByteNum:
            portName[0] = inData[inputReadingByte];
            CalcCRC ^= inData[inputReadingByte];
            outReadingByte++;
            break;

        case LBSportByteNum:
            portName[1] = inData[inputReadingByte];
            portName[2] = '\0';
            CalcCRC ^= inData[inputReadingByte];
            outReadingByte++;
            break;

        case MBSportByteNum:
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

void Sonars::dataResived(const SonarData data)
{

}

