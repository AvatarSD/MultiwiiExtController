#include "basestationiface.h"

BaseStationIface::BaseStationIface(QObject *parent):QSerialPort(parent)
{
    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(takeByte()));
    this->setDataBits(Data8);
    this->setFlowControl(NoFlowControl);
    this->setParity(NoParity);
    //this->setReadBufferSize(bufferSize);
}

BaseStationIface::~BaseStationIface()
{
    if(this->isOpen()) this->close();
}

void BaseStationIface::Connect(int *res, QString port, int baud)
{
    this->setBaudRate(baud);
    this->setPortName(port);
    *res = this->open(ReadWrite);
}

void BaseStationIface::Disconnect()
{
    this->close();
}

void BaseStationIface::takeByte()
{
    /*inputs*/
    int ByteToRead = this->bytesAvailable();
    QByteArray inData = this->read(ByteToRead);

    /*outputs*/
    static char * outHeader, * outData;// = new unsigned char[RX_Buffer];
    static unsigned int OutReadingByte = 0;
    static unsigned char headerLenth;
    static unsigned int cmdLenth;
    static unsigned char CmdCRC, CalcCRC = 0;

    for(int InputReadingByte = 0; InputReadingByte<ByteToRead; InputReadingByte++)
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
        else if((OutReadingByte >= strlen(startBytes))&&(OutReadingByte < strlen(startBytes)+sizeof(headerLenth)))
        {
            CalcCRC ^= inData[InputReadingByte];
            headerLenth = inData[InputReadingByte];
            headerLenth<<=((sizeof(headerLenth)-1)-(OutReadingByte-strlen(startBytes)))*8;
            if((sizeof(headerLenth)-1)==(OutReadingByte-strlen(startBytes))) outHeader = new char[headerLenth];
            OutReadingByte++;
        }

        //detect cmdLenth (big endian)
        else if((OutReadingByte >= strlen(startBytes)+sizeof(headerLenth))&&(OutReadingByte < strlen(startBytes)+sizeof(headerLenth)+sizeof(cmdLenth)))
        {
            CalcCRC ^= inData[InputReadingByte];
            cmdLenth = inData[InputReadingByte];
            cmdLenth<<=((sizeof(cmdLenth)-1)-(OutReadingByte-strlen(startBytes)-sizeof(headerLenth)))*8;
            if((sizeof(cmdLenth)-1)==(OutReadingByte-strlen(startBytes)-sizeof(headerLenth))) outData = new char[cmdLenth];
            OutReadingByte++;
        }

        //copy header
        else if((OutReadingByte >= strlen(startBytes)+sizeof(headerLenth)+sizeof(cmdLenth))&&
                (OutReadingByte < strlen(startBytes)+sizeof(headerLenth)+sizeof(cmdLenth)+headerLenth))
        {
            outHeader[OutReadingByte-(strlen(startBytes)+sizeof(headerLenth)+sizeof(cmdLenth))] = inData[InputReadingByte];
            OutReadingByte++;
            CalcCRC ^= inData[InputReadingByte];
        }

        //copy data
        else if((OutReadingByte >= strlen(startBytes)+sizeof(headerLenth)+sizeof(cmdLenth)+headerLenth)&&
                (OutReadingByte < strlen(startBytes)+sizeof(headerLenth)+sizeof(cmdLenth)+cmdLenth+headerLenth))
        {
            outData[OutReadingByte-(strlen(startBytes)+sizeof(headerLenth)+sizeof(cmdLenth)+headerLenth)] = inData[InputReadingByte];
            OutReadingByte++;
            CalcCRC ^= inData[InputReadingByte];
        }

        //detect and compare crc
        else if (OutReadingByte == strlen(startBytes)+sizeof(headerLenth)+sizeof(cmdLenth)+cmdLenth+headerLenth)
        {
            CmdCRC = inData[InputReadingByte];

            //Checking CRC
            if(CalcCRC==CmdCRC)
            {
                //call next func
                emit takeCmd(outHeader, outData, headerLenth, cmdLenth);
            }
            OutReadingByte = 0;
            CalcCRC = 0;
            delete [] outData;
            delete [] outHeader;
        }
       else if(OutReadingByte > strlen(startBytes)+sizeof(headerLenth)+sizeof(cmdLenth)+cmdLenth+headerLenth)
        {
            OutReadingByte = 0;
            CalcCRC = 0;
        }
    }
}

void BaseStationIface::giveCmd(char *header, char *messege, unsigned char headerLenth, unsigned int messegeLenth)
{
    char cheksum = 0;
    char * buf = new char[strlen(startBytes)+sizeof(headerLenth)+sizeof(messegeLenth)+headerLenth+messegeLenth+sizeof(cheksum)];

    //write start bytes
    for(unsigned int i = 0; i<strlen(startBytes); i++)
    {
        buf[i] = startBytes[i];
        cheksum ^= buf[i];
    }
    //write header Lenth
    for(unsigned int i = 0; i<sizeof(headerLenth); i++)
    {
        buf[i+strlen(startBytes)] = (headerLenth>>(((sizeof(headerLenth)-1)-i)*8))&0xFF;
        cheksum ^= buf[i+strlen(startBytes)];
    }
    //write command lenth
    for(unsigned int i = 0; i<sizeof(messegeLenth); i++)
    {
        buf[i+strlen(startBytes)+sizeof(headerLenth)] = (messegeLenth>>(((sizeof(messegeLenth)-1)-i)*8))&0xFF;
        cheksum ^= buf[i+strlen(startBytes)+sizeof(headerLenth)];
    }
    //write header
    for(unsigned int i = 0; i<headerLenth; i++)
    {
        buf[i+strlen(startBytes)+sizeof(headerLenth)+sizeof(messegeLenth)] = header[i];
        cheksum ^= buf[i+strlen(startBytes)+sizeof(headerLenth)+sizeof(messegeLenth)];
    }
    //write command
    for(unsigned int i = 0; i<messegeLenth; i++)
    {
        buf[i+strlen(startBytes)+sizeof(headerLenth)+sizeof(messegeLenth)+headerLenth] = messege[i];
        cheksum ^= buf[i+strlen(startBytes)+sizeof(headerLenth)+sizeof(messegeLenth)+headerLenth];
    }
    //write CRC
    buf[strlen(startBytes)+sizeof(headerLenth)+sizeof(messegeLenth)+headerLenth+messegeLenth] = cheksum;

    if(this->isOpen())
    {
        this->write(buf, strlen(startBytes)+sizeof(headerLenth)+sizeof(messegeLenth)+headerLenth+messegeLenth+sizeof(cheksum));
    }
    else emit disconnected();
    delete [] buf;
}
