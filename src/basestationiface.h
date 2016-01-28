#ifndef BASESTATIONIFACE_H
#define BASESTATIONIFACE_H

#include <QtSerialPort/QSerialPort>

#define startBytes      "$SD"
#define DefaultBasePort "/dev/ttyS1"
#define DefaultBaseBaud 115200
//#define bufferSize      512

class BaseStationIface : public QSerialPort
{
    Q_OBJECT

public:
    BaseStationIface(QObject *parent = 0);
    ~BaseStationIface();

private slots:
    void takeByte();
    void Disconnect();

signals:
    void takeCmd(char* header, char* messege, unsigned char headerLenth, unsigned int messegeLenth);
    void disconnected();

public slots:
    void giveCmd(char* header, char* messege, unsigned char headerLenth, unsigned int messegeLenth);
    void Connect(int *res, QString port=DefaultBasePort, int baud=DefaultBaseBaud);

private:


};

#endif // BASESTATIONIFACE_H
