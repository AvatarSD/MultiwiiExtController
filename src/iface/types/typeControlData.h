/*
 * types.h
 *
 *  Created on: 19 лип. 2015
 *      Author: sd
 */

#ifndef IFACE_TYPES_TYPECONTROLDATA_H_
#define IFACE_TYPES_TYPECONTROLDATA_H_


class ControlData
{
public:
	ControlData();
	~ControlData();

	int x;
	int y;
	int z;
	int oZ;

	ControlData operator + (const ControlData&);
	ControlData operator - (const ControlData&);
	void operator += (const ControlData&);
	void operator -= (const ControlData&);

	void zeroing();
};


#endif /* IFACE_TYPES_TYPECONTROLDATA_H_ */
