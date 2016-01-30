#ifndef SONARS_H
#define SONARS_H

#include "../BoostSerialPort/BSerialPort.h"

class SonarData
{
public:
    SonarData(const char *port, uint8_t portNum, uint16_t distance) :
        _port(port), _distance(distance), _portNum(portNum) {}
    SonarData(std::string port, uint8_t portNum, uint16_t distance) :
        _port(port), _distance(distance), _portNum(portNum) {}

    std::string getNameNum() const
    {
        std::string temp = _port + std::to_string((uint16_t)_portNum);
        return temp;
    }

    std::string getName() const
    {
        return _port;
    }

    uint16_t getNum() const
    {
        return _portNum;
    }

    uint16_t getDistance() const
    {
        return _distance;
    }

private:
    std::string _port;
    uint16_t _distance;
    uint8_t _portNum;

};


typedef std::map<uint8_t, uint8_t> TimingMap;

class Sonars
{
public:
    Sonars(AsyncIOStream & iface);

    std::function<void(const SonarData &)> dataResived;

    bool setTimingMap(const TimingMap & timingMap);
    TimingMap getTimingMap();

    bool setRelaxTime(uint8_t timingMap);
    uint8_t getRelaxTime();

    bool startMeasuring();
    bool stopMeasuring();

private:
    void read(const uint8_t * inData, uint32_t byteToRead);
    AsyncIOStream & _iface;
};

#endif // SONARS_H
