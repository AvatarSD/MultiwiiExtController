/*
 * MachineControl.cpp
 *
 *  Created on: 19 лип. 2015
 *      Author: sd
 */

#include "MachineControl.h"

MachineControl::MachineControl(): dataCorrection() {zeroingAfterMove = 1;}

MachineControl::~MachineControl(){}

void MachineControl::setMove(const ControlData& controldata)
{
	move(dataCorrection + controldata);
	if(zeroingAfterMove)dataCorrection.zeroing();
}


void MachineControl::setDiff(const ControlData& diffcontroldata)
{
	dataCorrection = dataCorrection + diffcontroldata;
}

