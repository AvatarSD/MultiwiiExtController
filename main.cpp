#include "mainwindow.h"
#include <QApplication>
#include "basestationiface.h"
#include "basestationcore.h"
#include "sonarsroutine.h"

#include <iostream>
#include <algorithm>
#include <PPM/ppm.h>

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}


int main(int argc, char *argv[])
{

    if(cmdOptionExists(argv, argv+argc, "-G"))
    {

         QApplication a(argc, argv);

        JoystickAdv * joy = new JoystickAdv();
        MainWindow w(joy);
        BaseStationIface * CopterIface = new BaseStationIface();
        BaseStationCore * Connector = new BaseStationCore();

//        Сделть наследованием!!
        QObject::connect(CopterIface, SIGNAL(takeCmd(char*,char*,unsigned char,uint)), Connector, SLOT(inCmd(char*,char*,unsigned char,uint)));
        QObject::connect(Connector, SIGNAL(outCmd(char*,char*,unsigned char,uint)),CopterIface, SLOT(giveCmd(char*,char*,unsigned char,uint)));

        QObject::connect(joy, SIGNAL(dataRsv(JoyData*)), Connector, SLOT(inJoyData(JoyData*)));
        QObject::connect(Connector, SIGNAL(outMetrik(mw_metric*)), &w, SLOT(metriIn(mw_metric *)));

//        Убрать!
        QObject::connect(&w, SIGNAL(Connect(int*,QString,int)),CopterIface, SLOT(Connect(int*,QString,int)));
        QObject::connect(&w, SIGNAL(DisconnSig()),CopterIface,SLOT(Disconnect()));

         w.show();

         return a.exec();
    }

    else if(cmdOptionExists(argv, argv+argc, "-S"))
    {
        //Sonars Test
        SonarsRoutine sonars(cmdOptionExists(argv, argv+argc, "-s"));
        std::cout << "port stat: " << sonars.BSerialPort::connect(getCmdOption(argv, argv + argc, "-p"))
                  << std::endl;
        while(1);
    }

    else if(cmdOptionExists(argv, argv+argc, "-R"))
    {
        //Sonars Test
        PPM rcInput;
        std::cout << "port stat: " << rcInput.BSerialPort::connect(getCmdOption(argv, argv + argc, "-p"))
                  << std::endl;
        while(1);
    }

std::cout << "no specific options"  << std::endl;


}
