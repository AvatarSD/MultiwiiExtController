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

    int getVal()
    {
        return _data;
    }

    std::string getName()
    {
        _name[3] = 0;
        return std::string(_name);
    }
    const char * getName_c()
    {
        _name[3] = 0;
        return _name;
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
    virtual void incomingData(const SonarsData & data);
    void read(const char * inData, int byteToRead);
};

#endif // SONARS_H
