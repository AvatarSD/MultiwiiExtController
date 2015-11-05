#ifndef SONARS_H
#define SONARS_H

#include "BoostSerialPort/BSerialPort.h"

class SonarsData
{
public:
    SonarsData();
    SonarsData(const char * name, int data)
    {
        memcpy(_name, name, 3);
        _name[3] = 0;
        _data = data;
    }


private:
    char _name[4];
    int _data;
};

class Sonars : public BSerialPort
{
public:
    Sonars();

private:
    virtual void incomingData(SonarsData data);
    void read(const char * inData, int byteToRead);
};

#endif // SONARS_H
