#include "basestationcore.h"
#include <cstring>

BaseStationCore::BaseStationCore()
{
    moveData = new mw_move;
}

BaseStationCore::~BaseStationCore()
{
delete moveData;
}

void BaseStationCore::inCmd(const uint8_t * header, const uint8_t * messege, uint8_t headLenth, uint32_t messegeLenth)
{

    if(0 == strcmp("metric", (const char*)header))
    	outMetrik((mw_metric*)messege);
}

void BaseStationCore::inJoyData(JoyData * data)
{
    moveData->THROTTLE = data->throt;
    moveData->YAW = data->yaw;
    moveData->PITCH= data->pich;
    moveData->ROLL = data->roll;
    moveData->AUX1 = data->aux1;
    moveData->AUX2 = data->aux2;
    moveData->AUX3 = 1500;
    moveData->AUX4 = 1500;

//    static int f = 0;
//    if(f++ == 2)
//    {
        outCmd((uint8_t*)"move", (uint8_t*)moveData, strlen("move"), 16);
//        f=0;
//    }


}

