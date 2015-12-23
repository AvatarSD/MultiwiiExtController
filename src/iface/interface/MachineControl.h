/*
 * iface.h
 *
 *  Created on: 18 лип. 2015
 *      Author: sd
 */

#ifndef IFACE_MACHINECONTROL_H_
#define IFACE_MACHINECONTROL_H_

#include "../types/control.h"
#include <list>

class MachineControl
{
public:
	MachineControl();
	virtual ~MachineControl();

	void setMove(const ControlData& controldata); // Range: -1000...+1000

	void registerControlPoint(ControlData* correctionDataPointer);
	void unRegisterControlPoint(ControlData* correctionDataPointer);

private:
	std::list<ControlData*> correctionList;

	virtual void move(const ControlData& controldata)
	{
	}
	ControlData dataCorrection;
};

#endif /* IFACE_MACHINECONTROL_H_ */
