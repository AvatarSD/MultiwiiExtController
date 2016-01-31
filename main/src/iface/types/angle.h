/*
 * angle.h
 *
 *  Created on: 19 лип. 2015
 *      Author: sd
 */

#ifndef IFACE_TYPES_ANGLE_H_
#define IFACE_TYPES_ANGLE_H_

class Angle
{
public:
	Angle();
	Angle(double oX, double oY, double oZ);
	~Angle();

	double oX, oY, oZ;
};

#endif /* IFACE_TYPES_ANGLE_H_ */
