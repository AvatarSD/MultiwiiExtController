/*
 * Copter.cpp
 *
 *  Created on: 19 лип. 2015
 *      Author: sd
 */

#include "Copter.h"
#include <cmath>

/*Macro settings*/
#define max_range 1000 //проверка входных значений

#define min 1000
#define mid 1500
#define max 2000

#define arm_ch AUX1
#define armed min
#define disarmed mid

#define mode_ch AUX2
#define angle_mode min
#define acro_mode mid
#define baro_mode max
/**/

#define CorrectionDisable 0
#define CorrectionByInputData 1
#define CorrectionByInputAngle 2

Copter::Copter() :
MachineControl(), MultiWii()
{
	_accelZeroGravity = 0;
	//	_throtCorrectionAngle.oX = 0;
	//	_throtCorrectionAngle.oY = 0;
	//	_throtCorrectionAngle.oZ = 0;
	//	_throtCorrectionMode = CorrectionByInputData;

	_controlData.AUX1 = mid;
	_controlData.AUX2 = mid;
	_controlData.AUX3 = mid;
	_controlData.AUX4 = mid;
	_controlData.THROTTLE = min;
	_controlData.PITCH = mid;
	_controlData.ROLL = mid;
	_controlData.YAW = mid;

	_controlData.arm_ch = armed;
	_controlData.mode_ch = angle_mode;
}

Copter::~Copter()
{
}

//void Copter::setAngle(Angle& throtCorrection)
//{
//	_throtCorrectionAngle = throtCorrection;
//}

void Copter::setArm(bool onoff)
{
	if (onoff)
		_controlData.arm_ch = armed;
	else
		_controlData.arm_ch = disarmed;
}

char Copter::isArmed()
{
	if (_controlData.arm_ch == armed)
		return 1;
	else if (_controlData.arm_ch == disarmed)
		return 0;
	else
		return -1;
}

//void Copter::setThrotCorrectionDisable()
//{_throtCorrectionMode = CorrectionDisable;}
//
//void Copter::setThrotCorrectionByInputData()
//{_throtCorrectionMode = CorrectionByInputData;}
//
//void Copter::setThrotCorrectionByInputAngle()
//{_throtCorrectionMode = CorrectionByInputAngle;}
//
//char Copter::getThrotCorrectionMode()
//{return _throtCorrectionMode;}

void Copter::setZeroGravityAccel(int Z_accel)
{
	_accelZeroGravity = Z_accel;
}

int Copter::getZeroGravityAccel()
{
	return _accelZeroGravity;
}

void Copter::applySettings()
{
	directMove(_controlData);
}

void Copter::move(const ControlData& controldata)
{
	//todo:
	//проверка границ
	//приведение значений(умное приведение значений, _controlData.THROTTLE < max, нахождение максимальных углов в зависимости от
	//ускорения висения)

	_controlData.YAW = controldata.oZ / 2 + mid;

	//	Angle angle;
	//	if (_throtCorrectionMode == CorrectionByInputData)
	//	{
	//		angle.oX = (((double) controldata.x) * M_PI_2) / max_range;
	//		angle.oY = (((double) controldata.y) * M_PI_2) / max_range;
	//	}
	//	else if (_throtCorrectionMode == CorrectionByInputAngle)
	//	{
	//		angle = _throtCorrectionAngle;
	//	}
	//	else
	//	{
	//		angle.oX = 0;
	//		angle.oY = 0;
	//	}

	//todo: Здесь корректировка углов.
	_controlData.PITCH = controldata.y / 2 + mid;
	_controlData.ROLL = controldata.x / 2 + mid;
	_controlData.THROTTLE = controldata.z + _accelZeroGravity;

	/*if ()
	 _controlData.THROTTLE = (_controlData.THROTTLE
	 * sqrt(pow(tan(angle.oX), 2) + pow(tan(angle.oY), 2) + 1))
	 / 2+ mid;*/

	directMove(_controlData);
}

