#include "joystickadv.h"
#include <iostream>
/*
18 Bytes, TX->PC

Byte [0,1]: Header, always [0x55, 0xFC]
Byte [2-15]: Payload, Potmeter values.
[2] MSB [3] LSB CH1
[4] MSB [5] LSB CH2
[6] MSB [7] LSB CH3
[8] MSB [9] LSB CH4
[10] MSB [11] LSB CH5
[12] MSB [13] LSB CH6
[14] MSB [15] LSB CH4 but between 0 and 1000?
Byte [16,17]: Checksum. All bytes of payload added up, MSB first.
*/

#define $55Byte             0
#define $FCByte             1
#define StartData_byte      2
#define MSB_CH4_byte        14
#define LSB_CH4_byte        15
#define MSB_Checksum_byte   16
#define LSB_Checksum_byte   17

#define dataByte 11


JoystickAdv::JoystickAdv() : BSerialPort()
{
    joydata = new JoyData();
}

JoystickAdv::~JoystickAdv()
{
    delete joydata;
}

void JoystickAdv::read(const uint8_t * data, int byteToRead)
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
                dataRsv(*joydata);
            OutReadingByte = 0;
            break;

        default:
            ((char*)joydata)[dataByte-(OutReadingByte-StartData_byte)] = inData[InputReadingByte];
            OutReadingByte++;
            break;

        }
    }
}

void JoystickAdv::disconnectEvent(std::string err)
{
    disconnected(err);
}
