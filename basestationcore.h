#ifndef BASESTATIONCORE_H
#define BASESTATIONCORE_H

#include <QObject>
#include "mwtypes.h"
#include "Joystick/JoystickAdv/joytypes.h"

class BaseStationCore : public QObject
{
    Q_OBJECT
public:
    explicit BaseStationCore(QObject *parent = 0);
    ~BaseStationCore();

private:
    mw_move * moveData;

signals:
    void outCmd(char* header, char* messege, unsigned char headerLenth, unsigned int messegeLenth);
    void outMetrik(mw_metric * data);
    void outMove(mw_move * data);

public slots:
    void inCmd(char* header, char* messege, unsigned char headLenth, unsigned int messegeLenth);
    void inJoyData(JoyData * data);
};

#endif // BASESTATIONCORE_H
