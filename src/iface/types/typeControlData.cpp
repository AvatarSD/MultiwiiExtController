/*
 * types.cpp
 *
 *  Created on: 19 лип. 2015
 *      Author: sd
 */
#include "typeControlData.h"

ControlData::ControlData(): x(0), y(0), z(0), oZ(0) {}

ControlData::~ControlData(){}

void ControlData::zeroing(){
	x = 0;
	y = 0;
	z = 0;
	oZ = 0;
}

ControlData ControlData::operator +(const ControlData& a)
{
	ControlData res;
	res.oZ = a.oZ + oZ;
	res.x = a.x + x;
	res.y = a.y + y;
	res.z = a.z + z;
	return res;
}

ControlData ControlData::operator -(const ControlData& a)
{
	ControlData res;
	res.oZ = oZ - a.oZ;
	res.x = x - a.x;
	res.y = y - a.y;
	res.z = z - a.z;
	return res;
}

void ControlData::operator += (const ControlData& a)
{
	oZ += a.oZ;
	x += a.x;
	y += a.y;
	z += a.z;

}

void ControlData::operator -=(const ControlData& a)
{
	oZ -= a.oZ;
	x -= a.x;
	y -= a.y;
	z -= a.z;
}
