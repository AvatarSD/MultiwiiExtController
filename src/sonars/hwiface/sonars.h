#ifndef SONARS_H
#define SONARS_H

#include "../BoostSerialPort/BSerialPort.h"

class SonarData
{
public:
    SonarData(const char *port, uint16_t distance) :
        _port(port), _distance(distance) {}
    SonarData(std::string port, uint16_t distance) :
        _port(port), _distance(distance) {}

    std::string getName()
    {
        return _port;
    }

    uint16_t getDistance()
    {
        return _distance;
    }

private:
    std::string _port;
    uint16_t _distance;
};

class Sonars : public BSerialPort
{
public:
    Sonars();

    void read(const uint8_t *inData, int byteToRead);

    virtual void dataResived(const SonarData data);
};

#endif // SONARS_H
