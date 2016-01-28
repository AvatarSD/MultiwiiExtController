#ifndef JOYSTICKADV_H
#define JOYSTICKADV_H

#include <QObject>
#include "joytypes.h"
#include "BoostSerialPort/BSerialPort.h"

class JoystickAdv : public QObject, public BSerialPort
{
    Q_OBJECT
public:
    explicit JoystickAdv(QObject *parent = 0);
    ~JoystickAdv();

signals:
    void dataRsv(JoyData * data);
    void disconnected(QString err);

private:
    JoyData * joydata;
    void read(const uint8_t *data, int byteToRead);
    void disconnectEvent(std::string err);

};

#endif // JOYSTICKADV_H
