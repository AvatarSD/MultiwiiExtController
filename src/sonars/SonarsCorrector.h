/*
 * SonarsCorrector.h
 *
 *  Created on: 21 груд. 2015
 *      Author: sd
 */

#ifndef SONARS_SONARSCORRECTOR_H_
#define SONARS_SONARSCORRECTOR_H_

#include "hwiface/sonars.h"
#include "../iface/types/control.h"
#include "../service/pid/PID.h"
#include "../service/timer/ThreadTimer.h"

class SonarsCorrector
{
public:
	SonarsCorrector(Sonars & sonarsIface);
	~SonarsCorrector();

	const ControlData * getCorrectionDataPointer();

private:
	ControlData _sonarCorrectionData;
	//PID _pidZ, _pidY, _pidX;
	//ThreadTimer _pidTimer;

	void inputData(const SonarData& data);
	void computePIDs();

	Sonars & _sonarsIface;
};

#endif /* SONARS_SONARSCORRECTOR_H_ */
