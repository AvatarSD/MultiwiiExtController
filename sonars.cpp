#include "sonars.h"

#define BUFF_LEN 32

#define $BYTE               0
#define START_NAME_BYTE     1
#define START_DATA_BYTE     4
#define Checksum_byte       6

Sonars::Sonars() : BSerialPort(BUFF_LEN)
{

}

void Sonars::incomingData(const SonarsData &data)
{

}

void Sonars::read(const char * inData, int byteToRead)
{
    /*outputs*/
    static char OutReadingByte = 0, buf[4];
    static unsigned char CalcCRC = '$';
    static short unsigned int data = 0;

    for(int InputReadingByte = 0; InputReadingByte<byteToRead; InputReadingByte++)
    {
        if(OutReadingByte == $BYTE) memset(buf, 0, 4);

        //detect some inportant for us data(number bytes in arrived command)

        if(OutReadingByte == $BYTE)
            OutReadingByte++;
        else if((OutReadingByte >= START_NAME_BYTE)&&(OutReadingByte < START_DATA_BYTE))
        {
            buf[OutReadingByte-START_NAME_BYTE] = inData[InputReadingByte];
            OutReadingByte++;
        }
        else if((OutReadingByte >= START_DATA_BYTE)&&(OutReadingByte < Checksum_byte))
        {
            ((unsigned char*)(&data))[OutReadingByte-START_DATA_BYTE] = inData[InputReadingByte];
            OutReadingByte++;
        }
        if(OutReadingByte >= Checksum_byte)
        {
            //CmdCRC = inData[InputReadingByte];
            OutReadingByte = 0;
            for(int i = 0; i < 3; i++)
                CalcCRC ^= buf[i];
            for(int i = 0; i < 2; i++)
                CalcCRC ^= ((unsigned char*)(&data))[i];
            if(CalcCRC == inData[InputReadingByte])
            {
                SonarsData sonarData(buf, data);
                incomingData(SonarsData(buf, sonarData));
            }
        }
    }
}
