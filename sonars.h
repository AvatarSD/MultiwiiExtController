#ifndef SONARS_H
#define SONARS_H

#include "BoostSerialPort/BSerialPort.h"

class Sonars : public BSerialPort
{
public:
    Sonars();

    void read(const char * inData, int byteToRead);

    virtual dataResived(std::string port, int distance);
};

#endif // SONARS_H
