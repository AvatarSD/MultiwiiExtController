#include "basestreamer.h"

BaseStreamer::BaseStreamer() : BSerialPort(){}

BaseStreamer::~BaseStreamer(){}

void BaseStreamer::read(char * inData, int byteToRead)
{
    /*outputs*/
    static char * outHeader, * outData;// = new unsigned char[RX_Buffer];
    static unsigned int OutReadingByte = 0;
    static unsigned char headerLength;
    static unsigned int cmdLength;
    static unsigned char CmdCRC, CalcCRC = 0;

    for(int InputReadingByte = 0; InputReadingByte<byteToRead; InputReadingByte++)
    {
        //detect startBytes
        if(OutReadingByte<strlen(startBytes))
        {
            if(inData[InputReadingByte] == startBytes[OutReadingByte])
            {
                OutReadingByte++;
                CalcCRC ^= inData[InputReadingByte];
            }
            else
            {
                OutReadingByte = 0;
                CalcCRC = 0;
            }
        }

        //detect headerLenth (big endian)
        else if((OutReadingByte >= strlen(startBytes))&&(OutReadingByte < strlen(startBytes)+sizeof(headerLength)))
        {
            CalcCRC ^= inData[InputReadingByte];
            headerLength = inData[InputReadingByte];
            headerLength<<=((sizeof(headerLength)-1)-(OutReadingByte-strlen(startBytes)))*8;
            if((sizeof(headerLength)-1)==(OutReadingByte-strlen(startBytes))) outHeader = new char[headerLength];
            OutReadingByte++;
        }

        //detect cmdLenth (big endian)
        else if((OutReadingByte >= strlen(startBytes)+sizeof(headerLength))&&(OutReadingByte < strlen(startBytes)+sizeof(headerLength)+sizeof(cmdLength)))
        {
            CalcCRC ^= inData[InputReadingByte];
            cmdLength = inData[InputReadingByte];
            cmdLength<<=((sizeof(cmdLength)-1)-(OutReadingByte-strlen(startBytes)-sizeof(headerLength)))*8;
            if((sizeof(cmdLength)-1)==(OutReadingByte-strlen(startBytes)-sizeof(headerLength))) outData = new char[cmdLength];
            OutReadingByte++;
        }

        //copy header
        else if((OutReadingByte >= strlen(startBytes)+sizeof(headerLength)+sizeof(cmdLength))&&
                (OutReadingByte < strlen(startBytes)+sizeof(headerLength)+sizeof(cmdLength)+headerLength))
        {
            outHeader[OutReadingByte-(strlen(startBytes)+sizeof(headerLength)+sizeof(cmdLength))] = inData[InputReadingByte];
            OutReadingByte++;
            CalcCRC ^= inData[InputReadingByte];
        }

        //copy data
        else if((OutReadingByte >= strlen(startBytes)+sizeof(headerLength)+sizeof(cmdLength)+headerLength)&&
                (OutReadingByte < strlen(startBytes)+sizeof(headerLength)+sizeof(cmdLength)+cmdLength+headerLength))
        {
            outData[OutReadingByte-(strlen(startBytes)+sizeof(headerLength)+sizeof(cmdLength)+headerLength)] = inData[InputReadingByte];
            OutReadingByte++;
            CalcCRC ^= inData[InputReadingByte];
        }

        //detect and compare crc
        else if (OutReadingByte == strlen(startBytes)+sizeof(headerLength)+sizeof(cmdLength)+cmdLength+headerLength)
        {
            CmdCRC = inData[InputReadingByte];

            //Checking CRC
            if(CalcCRC==CmdCRC)
            {
                //call next func
                takeCmd(outHeader, outData, headerLength, cmdLength);
            }
            OutReadingByte = 0;
            CalcCRC = 0;
            delete [] outData;
            delete [] outHeader;
        }
       else if(OutReadingByte > strlen(startBytes)+sizeof(headerLength)+sizeof(cmdLength)+cmdLength+headerLength)
        {
            OutReadingByte = 0;
            CalcCRC = 0;
        }
    }
}

void BaseStreamer::sendCmd(char *header, char *message, unsigned char headerLength, unsigned int messageLength)
{
    char cheksum = 0;
    char * buf = new char[strlen(startBytes)+sizeof(headerLength)+sizeof(messageLength)+headerLength+messageLength+sizeof(cheksum)];

    //write start bytes
    for(unsigned int i = 0; i<strlen(startBytes); i++)
    {
        buf[i] = startBytes[i];
        cheksum ^= buf[i];
    }
    //write header Lenth
    for(unsigned int i = 0; i<sizeof(headerLength); i++)
    {
        buf[i+strlen(startBytes)] = (headerLength>>(((sizeof(headerLength)-1)-i)*8))&0xFF;
        cheksum ^= buf[i+strlen(startBytes)];
    }
    //write command lenth
    for(unsigned int i = 0; i<sizeof(messageLength); i++)
    {
        buf[i+strlen(startBytes)+sizeof(headerLength)] = (messageLength>>(((sizeof(messageLength)-1)-i)*8))&0xFF;
        cheksum ^= buf[i+strlen(startBytes)+sizeof(headerLength)];
    }
    //write header
    for(unsigned int i = 0; i<headerLength; i++)
    {
        buf[i+strlen(startBytes)+sizeof(headerLength)+sizeof(messageLength)] = header[i];
        cheksum ^= buf[i+strlen(startBytes)+sizeof(headerLength)+sizeof(messageLength)];
    }
    //write command
    for(unsigned int i = 0; i<messageLength; i++)
    {
        buf[i+strlen(startBytes)+sizeof(headerLength)+sizeof(messageLength)+headerLength] = message[i];
        cheksum ^= buf[i+strlen(startBytes)+sizeof(headerLength)+sizeof(messageLength)+headerLength];
    }
    //write CRC
    buf[strlen(startBytes)+sizeof(headerLength)+sizeof(messageLength)+headerLength+messageLength] = cheksum;

    this->write(buf, strlen(startBytes)+sizeof(headerLength)+sizeof(messageLength)+headerLength+messageLength+sizeof(cheksum));

    delete [] buf;
}

void BaseStreamer::takeCmd(char* header, char* message, unsigned char headerLength, unsigned int messegeLength)
{

}
