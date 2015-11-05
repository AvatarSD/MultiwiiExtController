#ifndef SONARSROUTINE_H
#define SONARSROUTINE_H

#include <QObject>
#include "sonars.h"

class SonarsRoutine : public QObject, public Sonars
{
    Q_OBJECT
public:
    explicit SonarsRoutine(QObject *parent = 0);

signals:
    void incomingDataRsv(const SonarsData * data);

private:
    void incomingData(const SonarsData & data);
};

#endif // SONARSROUTINE_H
