/*
 * SonarsCorrector.cpp
 *
 *  Created on: 21 груд. 2015
 *      Author: sd
 */

#include "SonarsCorrector.h"

SonarsCorrector::~SonarsCorrector()
{
	// TODO sonar corrector
}

SonarsCorrector::SonarsCorrector(Sonars& sonarsIface) :
		_sonarsIface(sonarsIface)
{
	//_pidX();

	_sonarsIface.dataResived = std::bind(&SonarsCorrector::inputData, this,
			std::placeholders::_1);

	_pidTimer.callback = std::bind(&SonarsCorrector::computePIDs, this);
	_pidTimer.start();
}

const ControlData* SonarsCorrector::getCorrectionDataPointer()
{
	return &_sonarCorrectionData;
}

void SonarsCorrector::inputData(const SonarData& data)
{
}

void SonarsCorrector::computePIDs()
{
	_pidX.compute();
	_pidY.compute();
	_pidZ.compute();
}
