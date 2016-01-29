/*
 * by S.D.
 */

#include "StreamReader/streamreader.h"

#include "consoleOut/sonarsroutine.h"
#include "consoleOut/PPMroutine.h"

#include "core/basestationcore.h"

#include <iostream>
#include <algorithm>

#include "argpars/argparser.h"

int main(int argc, char *argv[])
{

	if (cmdOptionExists(argv, argv + argc, "-G"))
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

	else if (cmdOptionExists(argv, argv + argc, "-S"))
	{
		//Sonars Test
		Sonars sonars;

		SonarsRoutine sonarsroutine(sonars);
		sonarsroutine.setMode(cmdOptionExists(argv, argv + argc, "-s"));

		std::cout << "port stat: "
				<< sonars.BSerialPort::connect(
						getCmdOption(argv, argv + argc, "-p")) << std::endl;
		while (1)
			;
	}

	else if (cmdOptionExists(argv, argv + argc, "-R"))
	{
		//Sonars Test
		PPM rcInput;

		PPMroutine ppmroutine(rcInput);
		if (!cmdOptionExists(argv, argv + argc, "-a"))
			ppmroutine.setup(PPMroutine::MAIN);
		else
			ppmroutine.setup(PPMroutine::ADDITIONAL);

		std::cout << "port stat: "
				<< rcInput.BSerialPort::connect(
						getCmdOption(argv, argv + argc, "-p")) << std::endl;
		while (1)
			;
	}

	std::cout << "no specific options" << std::endl;

}
