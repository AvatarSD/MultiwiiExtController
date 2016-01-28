
#include "basestationiface.h"
#include "basestationcore.h"
#include "sonarsroutine.h"

#include <iostream>
#include <algorithm>
#include <PPM/ppm.h>

#include "argparser.h"
#include "argp.h"


#define THR_CH 3
#define YAW_CH 4
#define ROLL_CH 2
#define PITH_CH 1

void stdOutControl(const std::list<RC> & data)
{
    printf( "\033[2J" );
    for(auto it = data.begin(); it != data.end(); it++)
    {
        switch (it->channel()+1) {
        case THR_CH:
            std::cout << "THR: " << it->value() << std::endl;
            break;
        case YAW_CH:
            std::cout << "YAW: " << it->value() << std::endl;
            break;
        case ROLL_CH:
            std::cout << "ROLL: " << it->value() << std::endl;
            break;
        case PITH_CH:
            std::cout << "PITH: " << it->value() << std::endl;
            break;
        default:
            break;
        }
    }
}

void stdOutAdditional(const std::list<RC> & data)
{
    printf( "\033[2J" );
    std::cout << std::endl << std::endl << std::endl << std::endl;
    for(auto it = data.begin(); it != data.end(); it++)
        std::cout << "Num: " << (uint16_t)it->channel() << " \tVal: " << it->value() << std::endl;
}

//void PPM::stdOut(const RC & data)
//{
//    if(data.channel() == 0)
//        printf( "\033[2J" );
//    std::cout << "Channel: " << (uint16_t)data.channel() << " \tValue: " << data.value() << std::endl;
//}

int main(int argc, char *argv[])
{

    if(cmdOptionExists(argv, argv+argc, "-G"))
    {
//
//        QApplication a(argc, argv);
//
//        JoystickAdv * joy = new JoystickAdv();
//        MainWindow w(joy);
//        BaseStationIface * CopterIface = new BaseStationIface();
//        BaseStationCore * Connector = new BaseStationCore();
//
//        //        Сделть наследованием!!
//        QObject::connect(CopterIface, SIGNAL(takeCmd(char*,char*,unsigned char,uint)), Connector, SLOT(inCmd(char*,char*,unsigned char,uint)));
//        QObject::connect(Connector, SIGNAL(outCmd(char*,char*,unsigned char,uint)),CopterIface, SLOT(giveCmd(char*,char*,unsigned char,uint)));
//
//        QObject::connect(joy, SIGNAL(dataRsv(JoyData*)), Connector, SLOT(inJoyData(JoyData*)));
//        QObject::connect(Connector, SIGNAL(outMetrik(mw_metric*)), &w, SLOT(metriIn(mw_metric *)));
//
//        //        Убрать!
//        QObject::connect(&w, SIGNAL(Connect(int*,QString,int)),CopterIface, SLOT(Connect(int*,QString,int)));
//        QObject::connect(&w, SIGNAL(DisconnSig()),CopterIface,SLOT(Disconnect()));
//
//        w.show();
//
//        return a.exec();
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
        if(cmdOptionExists(argv, argv+argc, "-a"))
        {
            rcInput.controlData = [](const std::list<RC>&){};//&stdOutControl;
            rcInput.additionalData = &stdOutAdditional;
        }
        else
        {
            rcInput.controlData = &stdOutControl;
            rcInput.additionalData = [](const std::list<RC>&){};//&stdOutAdditional;
        }
        std::cout << "port stat: " << rcInput.BSerialPort::connect(getCmdOption(argv, argv + argc, "-p"))
                  << std::endl;
        while(1);
    }

    std::cout << "no specific options"  << std::endl;


}
