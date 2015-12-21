/*
 * SonarsCorrector.h
 *
 *  Created on: 21 груд. 2015
 *      Author: sd
 */

#ifndef SONARS_SONARSCORRECTOR_H_
#define SONARS_SONARSCORRECTOR_H_

#include "../pid/PID.h"

class SonarsCorrector: public PID
{
public:
	SonarsCorrector();
	~SonarsCorrector();


};

#endif /* SONARS_SONARSCORRECTOR_H_ */
