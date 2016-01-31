#ifndef JOYSTICKADV_H
#define JOYSTICKADV_H

#include "joytypes.h"
#include "../../BoostSerialPort/BSerialPort.h"

class JoystickAdv
{
public:
    JoystickAdv(AsyncIOStream & iface);
    ~JoystickAdv();

    std::function<void(const JoyData&)> dataRsv;
    std::function<void(const std::string&)> disconnected;

private:
    JoyData joydata;
    void read(const uint8_t * inData, uint32_t byteToRead);
    AsyncIOStream & _iface;
};

#endif // JOYSTICKADV_H
