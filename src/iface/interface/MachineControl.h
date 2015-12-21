/*
 * iface.h
 *
 *  Created on: 18 лип. 2015
 *      Author: sd
 */

#ifndef IFACE_MACHINECONTROL_H_
#define IFACE_MACHINECONTROL_H_

#include "../types/control.h"
#include <map>

class MachineControl
{
public:
	MachineControl();
	virtual ~MachineControl();

	void setMove(const ControlData& controldata); // Range: -1000...+1000
	//void setDiff(const ControlData& diffcontroldata);

	//bool zeroingAfterMove;
	void registerControlPoint(std::string name, ControlData& correctiondata);
	void unRegisterControlPoint(std::string name);

private:
	std::map<std::string, ControlData&> correctionList;

	virtual void move(const ControlData& controldata)
	{
	}
	ControlData dataCorrection;
};

#endif /* IFACE_MACHINECONTROL_H_ */
