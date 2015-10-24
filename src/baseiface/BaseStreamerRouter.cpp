/*
 * BaseStreamerRouter.cpp
 *
 *  Created on: 18 лип. 2015
 *      Author: sd
 */

#include "BaseStreamerRouter.h"

BaseStreamerRouter::BaseStreamerRouter()  : BaseStreamer(){}

BaseStreamerRouter::~BaseStreamerRouter(){}

void BaseStreamerRouter::takeCmd(char* header, char* message,
	    		unsigned char headerLength, unsigned int messageLenth)
	{
//		std::cout << "Header lendht: " << (int)headerLength
//				<< "\tMessage lenght: " << messageLenth
//				<< std::endl;
		if(0 == std::strcmp(header, "move")) mwDirectControl((mw_move*)message);
	}

void BaseStreamerRouter::sendMetric(mw_metric * _metricData)
	{
		this->sendCmd((char*)std::string("metric").c_str(), ((char*)_metricData), 6, sizeof(mw_metric));
	}
