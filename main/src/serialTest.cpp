//============================================================================
// Name        : serialTest.cpp
// Author      : S.D.
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>

#include "baseiface/BaseStreamerRouter.h"
#include "copter/Copter.h"

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

int main(int argc, char ** argv)
{
	std::string mw_portname = argv[1];
	std::string bs_portname = argv[2];
	BaseStreamerRouter * bsconnection = new BaseStreamerRouter();
	Copter * multiwii = new Copter();

	std::cout << "MultiWii - (local) - by S.D.  port: "<< mw_portname << std::endl;
	std::cout << "Connection status is: " << multiwii->connect(mw_portname, 115200) << std::endl;
	std::cout << "BaseSation - (local) - by S.D.  port: "<< bs_portname << std::endl;
	std::cout << "Connection status is: " << bsconnection->connect(bs_portname) << std::endl;

	mw_move moveSample;
	moveSample.AUX1=moveSample.AUX2=moveSample.AUX3=moveSample.AUX4=
			moveSample.PITCH=moveSample.ROLL=moveSample.YAW = 1500;
	moveSample.THROTTLE=1000;

	bsconnection->mwDirectControl.connect([&](mw_move * move){moveSample = *move;});   //boost::bind(&MultiWii::move, multiwii, _1));
	multiwii->metricRecived.connect(boost::bind(&BaseStreamerRouter::sendMetric, bsconnection, _1));

	while(true)
	{
		multiwii->directMove(moveSample);
		usleep(4000);
	}

	return 0;
}
