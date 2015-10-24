/*
 * iface.h
 *
 *  Created on: 18 лип. 2015
 *      Author: sd
 */

#ifndef IFACE_MACHINECONTROL_H_
#define IFACE_MACHINECONTROL_H_

#include "types/typeControlData.h"

class MachineControl
{
public:
	MachineControl();
	virtual ~MachineControl();

	void setMove(const ControlData& controldata); // Range: -1000...+1000
	void setDiff(const ControlData& diffcontroldata);

	bool zeroingAfterMove;

private:
	virtual void move(const ControlData& controldata){}
	ControlData dataCorrection;
};


#endif /* IFACE_MACHINECONTROL_H_ */
