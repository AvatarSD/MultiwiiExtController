/*
 * ppmroutine.cpp
 *
 *  Created on: 29 січ. 2016
 *      Author: sd
 */

#include "PPMroutine.h"
#include <iostream>

PPMroutine::PPMroutine(PPM& iface) :
		_iface(iface), _mode(MAIN)
{
	using namespace std::placeholders;
	_iface.controlData = std::bind(&PPMroutine::stdOutControl, this, _1);
	_iface.additionalData = std::bind(&PPMroutine::stdOutAdditional, this, _1);
	_iface.rawDataResived = std::bind(&PPMroutine::stdOut, this, _1);

}

PPMroutine::~PPMroutine()
{

}

void PPMroutine::stdOutControl(const std::list<RC> & data)
{
	if(_mode != MAIN)
		return;
	printf("\033[2J");
	for (auto it = data.begin(); it != data.end(); it++)
	{
		switch (it->channel() + 1)
		{
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

void PPMroutine::stdOutAdditional(const std::list<RC> & data)
{
	if(_mode != ADDITIONAL)
		return;
	printf("\033[2J");
	std::cout << std::endl << std::endl << std::endl << std::endl;
	for (auto it = data.begin(); it != data.end(); it++)
		std::cout << "Num: " << (uint16_t) it->channel() << " \tVal: "
				<< it->value() << std::endl;
}

void PPMroutine::setup(SetupMode mode)
{
	_mode = mode;
}

void PPMroutine::stdOut(const RC & data)
{
	if(_mode != RAW)
		return;
	if (data.channel() == 0)
		printf("\033[2J");
	std::cout << "Channel: " << (uint16_t) data.channel() << " \tValue: "
			<< data.value() << std::endl;
}

