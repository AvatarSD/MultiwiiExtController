/*
 * Copter.h
 *
 *  Created on: 19 лип. 2015
 *      Author: sd
 */

#ifndef COPTER_COPTER_H_
#define COPTER_COPTER_H_

#include "../iface/interface/MachineControl.h"
#include "../iface/types/angle.h"
#include "mwiface/multiwii.h"

class Copter: public MachineControl, public MultiWii
{
public:
	Copter();
	~Copter();

	void setAngle(Angle& throtCorrection);
	void setArm();
	void setDisarm();
	char isArmed(); // 1 is armed, 0 is disarmed, -1 if other
	void setThrotCorrectionDisable();
	void setThrotCorrectionByInputData();
	void setThrotCorrectionByInputAngle();
	char getThrotCorrectionMode();
	void setZeroGravityAccel(int Z_accel);
	int  getZeroGravityAccel();
	void applySettings();
	//Что нужно сднлать в драйвере:
	//1. таймер запросов
	//2. //коректирующие ускорения
	//3. //корекция по углам
	//4. //некое управление

private:
	void move(const ControlData& controldata);

	Angle _throtCorrectionAngle;
	char _throtCorrectionMode;
	int _accelZeroGravity;
	mw_move _controlData;
};

#endif /* COPTER_COPTER_H_ */
