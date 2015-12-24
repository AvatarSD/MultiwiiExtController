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

class SonarsCorrector
{
public:
	SonarsCorrector(Sonars & sonarsIface);
	~SonarsCorrector();

	const ControlData * getCorrectionDataPointer();

private:
	SonarsCorrector();

	ControlData sonarCorrectionData;
	PID pidZ, pidY, pidX;

	void inputData(SonarData& data);
	void computePIDs();


};

#endif /* SONARS_SONARSCORRECTOR_H_ */
