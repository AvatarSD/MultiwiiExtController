#include "basestationcore.h"
#include <cstring>

BaseStationCore::BaseStationCore(QObject *parent) : QObject(parent)
{
    moveData = new mw_move;
}

BaseStationCore::~BaseStationCore()
{

}

void BaseStationCore::inCmd(char* header, char* messege, unsigned char headLenth, unsigned int messegeLenth)
{

    if(0 == std::strcmp("metric", header)) emit outMetrik((mw_metric*)messege);
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
//    if(f == 2)
//    {
        emit outCmd("move", (char*)moveData, strlen("move"), 16);
//        f=0;
//    }
//    f++;

}

