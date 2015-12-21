/*
 * MachineControl.cpp
 *
 *  Created on: 19 лип. 2015
 *      Author: sd
 */

#include "MachineControl.h"

MachineControl::MachineControl() :
		dataCorrection()
{
}

MachineControl::~MachineControl()
{
}

void MachineControl::setMove(const ControlData& controldata)
{
	dataCorrection.zeroing();
	for (auto it = correctionList.begin(); it != correctionList.end(); it++)
		dataCorrection += it->second;
	move(dataCorrection);
}

void MachineControl::registerControlPoint(std::string name,
		ControlData& correctionData)
{
	correctionList.insert(
			std::pair<std::string, ControlData&>(name, correctionData));
}

void MachineControl::unRegisterControlPoint(std::string name)
{
	correctionList.erase(correctionList.find(name));
}
