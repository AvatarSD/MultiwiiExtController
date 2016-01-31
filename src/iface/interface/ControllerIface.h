/*
 * ControllerIface.h
 *
 *  Created on: 9 січ. 2016
 *      Author: sd
 */

#ifndef IFACE_INTERFACE_CONTROLLERIFACE_H_
#define IFACE_INTERFACE_CONTROLLERIFACE_H_

#include <boost/signals2.hpp>
//#include <signal.h>
#include "../types/control.h"

class ControllerIface
{
public:
	ControllerIface();
	virtual ~ControllerIface();


	boost::signals2<void(ControlData&)> controlData;

};

#endif /* IFACE_INTERFACE_CONTROLLERIFACE_H_ */
