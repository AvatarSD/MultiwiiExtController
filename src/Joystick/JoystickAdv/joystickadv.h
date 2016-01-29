#ifndef JOYSTICKADV_H
#define JOYSTICKADV_H

#include "joytypes.h"
#include "../../BoostSerialPort/BSerialPort.h"

class JoystickAdv : public BSerialPort
{
public:
    explicit JoystickAdv();
    ~JoystickAdv();

    std::function<void(const JoyData&)> dataRsv;
    std::function<void(const std::string&)> disconnected;

private:
    JoyData * joydata;
    void read(const uint8_t *data, int byteToRead);
    void disconnectEvent(std::string err);

};

#endif // JOYSTICKADV_H
