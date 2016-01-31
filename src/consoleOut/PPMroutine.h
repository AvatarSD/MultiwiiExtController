/*
 * ppmroutine.h
 *
 *  Created on: 29 січ. 2016
 *      Author: sd
 */

#ifndef CONSOLEOUT_PPMROUTINE_H_
#define CONSOLEOUT_PPMROUTINE_H_

#include "../PPM/ppm.h"


class PPMroutine
{
public:
	PPMroutine(PPM&);
	~PPMroutine();

	enum SetupMode
	{
		RAW, MAIN, ADDITIONAL
	};

	void setup(SetupMode mode);

private:
	void stdOutControl(const std::list<RC> & data);
	void stdOutAdditional(const std::list<RC> & data);
	void stdOut(const RC & data);

	PPM& _iface;
	SetupMode _mode;
};

#endif /* CONSOLEOUT_PPMROUTINE_H_ */
