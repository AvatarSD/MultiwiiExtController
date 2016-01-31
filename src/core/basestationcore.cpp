#include "basestationcore.h"
#include <cstring>

BaseStationCore::BaseStationCore(StreamReader & reader) :
		_reader(reader)
{
	_reader.takeCmd = std::bind(&BaseStationCore::inCmd, this,
			std::placeholders::_1);
}

BaseStationCore::~BaseStationCore()
{

}

void BaseStationCore::inCmd(const Message & message)
{

	if (0 == strcmp("metric", (const char*) message.header))
		outMetrik((mw_metric*) message.data);
}

void BaseStationCore::inJoyData(const JoyData & data)
{
	moveData.THROTTLE = data.throt;
	moveData.YAW = data.yaw;
	moveData.PITCH = data.pich;
	moveData.ROLL = data.roll;
	moveData.AUX1 = data.aux1;
	moveData.AUX2 = data.aux2;
	moveData.AUX3 = 1500;
	moveData.AUX4 = 1500;

//    static int f = 0;
//    if(f++ == 2)
//    {
	_reader.sendCmd(
			Message((uint8_t*) "move", (uint8_t*) &moveData, strlen("move"),
					16));
//        f=0;
//    }

}

