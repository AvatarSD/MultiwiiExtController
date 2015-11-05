#include "sonarsroutine.h"

SonarsRoutine::SonarsRoutine(QObject *parent) : QObject(parent), Sonars()
{

}

void incomingData(const SonarsData & data)
{
    emit incomingDataRsv(data);
}
