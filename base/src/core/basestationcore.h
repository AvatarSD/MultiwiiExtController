#ifndef BASESTATIONCORE_H
#define BASESTATIONCORE_H


#include "mwtypes.h"
#include "../Joystick/JoystickAdv/joytypes.h"
#include <inttypes.h>
#include <functional>
#include "../StreamReader/streamreader.h"

class BaseStationCore
{
public:
    BaseStationCore(StreamReader & reader);
    ~BaseStationCore();

    void inCmd(const Message & message);
    void inJoyData(const JoyData & data);

private:
    mw_move moveData;
    std::function<void(const mw_metric*)> outMetrik;
    StreamReader & _reader;
};

#endif // BASESTATIONCORE_H
