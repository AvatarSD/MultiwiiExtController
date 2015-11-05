#include "sonars.h"

#define BUFF_LEN 32

Sonars::Sonars() : BSerialPort(BUFF_LEN)
{

}

void Sonars::incomingData(SonarsData data)
{

}

void Sonars::read(const char * inData, int byteToRead)
{
    /*inputs*/
    unsigned char * inData = (unsigned char *)data;

    /*outputs*/
    static char OutReadingByte = 0;
    static short int CmdCRC, CalcCRC;

    for(int InputReadingByte = 0; InputReadingByte<byteToRead; InputReadingByte++)
    {
        if(OutReadingByte==0) memset(joydata, 0, sizeof(JoyData));

        //detect some inportant for us data(number bytes in arrived command)
        switch (OutReadingByte)
        {
        case $55Byte:
            if(inData[InputReadingByte] != 0x55) OutReadingByte = 0; else OutReadingByte++;
            break;

        case $FCByte:
            if(inData[InputReadingByte] != 0xFC) OutReadingByte = 0; else OutReadingByte++;
            break;

        case MSB_CH4_byte:
            CalcCRC = 0;
            CalcCRC += inData[InputReadingByte];
            OutReadingByte++;
            break;

        case LSB_CH4_byte:
            CalcCRC += inData[InputReadingByte];
            OutReadingByte++;
            break;

        case MSB_Checksum_byte:
            CmdCRC = 0;
            CmdCRC += (unsigned short int)(inData[InputReadingByte] << 8 );
            OutReadingByte++;
            break;

        case LSB_Checksum_byte:
            CmdCRC += inData[InputReadingByte];
            for(unsigned char i = 0; i < sizeof(JoyData); i++) CalcCRC += ((unsigned char*)joydata)[i];
            if(CmdCRC == CalcCRC)
                emit dataRsv(joydata);
            OutReadingByte = 0;
            break;

        default:
            ((char*)joydata)[dataByte-(OutReadingByte-StartData_byte)] = inData[InputReadingByte];
            OutReadingByte++;
            break;

        }
    }
}
