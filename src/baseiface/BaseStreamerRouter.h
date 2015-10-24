/*
 * BaseStreamerRouter.h
 *
 *  Created on: 18 лип. 2015
 *      Author: sd
 */

#ifndef BASEIFACE_BASESTREAMERROUTER_H_
#define BASEIFACE_BASESTREAMERROUTER_H_

#include "basestreamer.h"
#include <boost/signals2.hpp>
#include "../mwiface/mwtypes.h"

class BaseStreamerRouter : public BaseStreamer
{
public:
	BaseStreamerRouter();
	~BaseStreamerRouter();

	boost::signals2::signal<void(mw_move *)> mwDirectControl;

	void sendMetric(mw_metric * _metricData);

private:
	void takeCmd(char* header, char* message,
	    		unsigned char headerLength, unsigned int messageLenth);
};

#endif /* BASEIFACE_BASESTREAMERROUTER_H_ */
