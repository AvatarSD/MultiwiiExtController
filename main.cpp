#include "mainwindow.h"
#include <QApplication>
#include "basestationiface.h"
#include "basestationcore.h"
#include "sonarsroutine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    JoystickAdv * joy = new JoystickAdv();
    MainWindow w(joy);
    BaseStationIface * CopterIface = new BaseStationIface();
    BaseStationCore * Connector = new BaseStationCore();

    //Сделть наследованием!!
    QObject::connect(CopterIface, SIGNAL(takeCmd(char*,char*,unsigned char,uint)), Connector, SLOT(inCmd(char*,char*,unsigned char,uint)));
    QObject::connect(Connector, SIGNAL(outCmd(char*,char*,unsigned char,uint)),CopterIface, SLOT(giveCmd(char*,char*,unsigned char,uint)));

    QObject::connect(joy, SIGNAL(dataRsv(JoyData*)), Connector, SLOT(inJoyData(JoyData*)));
    QObject::connect(Connector, SIGNAL(outMetrik(mw_metric*)), &w, SLOT(metriIn(mw_metric *)));

    //Убрать!
    QObject::connect(&w, SIGNAL(Connect(int*,QString,int)),CopterIface, SLOT(Connect(int*,QString,int)));
    QObject::connect(&w, SIGNAL(DisconnSig()),CopterIface,SLOT(Disconnect()));


    //Sonars Test
    SonarsRoutine sonars;
    QObject::connect(&sonars, SIGNAL(incomingDataRsv(const SonarsData &)),
                     &w, SLOT(showSnarsData(const SonarsData &)));
    sonars.connect(std::string("/dev/ttyUSB0"), 115200);

    w.show();

    return a.exec();
}
