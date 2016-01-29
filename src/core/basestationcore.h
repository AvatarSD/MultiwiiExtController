#ifndef BASESTATIONCORE_H
#define BASESTATIONCORE_H


#include "mwtypes.h"
#include "../Joystick/JoystickAdv/joytypes.h"
#include <inttypes.h>
#include <functional>

class BaseStationCore
{
public:
    BaseStationCore();
    ~BaseStationCore();

    void inCmd(const uint8_t *, const uint8_t *, uint8_t, uint32_t);
    void inJoyData(JoyData * data);

private:
    //mw_move * moveData;

  //  std::function<void(const uint8_t *, const uint8_t *, uint8_t, uint32_t)> outCmd;
    std::function<void(mw_metric*)> outMetrik;
    void outMove(mw_move * data);

};

#endif // BASESTATIONCORE_H
