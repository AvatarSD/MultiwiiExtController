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

void MachineControl::setMove(const ControlData & controldata)
{
	dataCorrection = controldata;
	for (auto it = correctionList.begin(); it != correctionList.end(); it++)
		dataCorrection += **it;
	move(dataCorrection);
}

void MachineControl::registerControlPoint(ControlData* correctionDataPointer)
{
	correctionList.push_back(correctionDataPointer);
}

void MachineControl::unRegisterControlPoint(ControlData* correctionDataPointer)
{
	correctionList.remove(correctionDataPointer);
}
