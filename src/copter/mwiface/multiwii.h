/*
 * multiwii.h
 *
 *  Created on: Jul 1, 2015
 *      Author: sd
 */

#ifndef COPTER_MWIFACE_MULTIWII_H_
#define COPTER_MWIFACE_MULTIWII_H_

#include <boost/signals2.hpp>
#include "../../BoostSerialPort/BSerialPort.h"
#include "mwtypes.h"

class MultiWii : public BSerialPort
{
public:
    MultiWii();// : BSerialPort();
    ~MultiWii();

    // Call this method for send request
	void directMove(const mw_move& data);
	void getStatus();
	void getMetric();
	void getGPS();
	void getAnalog();
	void getMWInfo();
	void getAltitude();
	void getAttitude();

	// Subscribe this signals to take notification
	boost::signals2::signal<void (mw_metric*)> metricRecived;
	boost::signals2::signal<void (mw_status*)> statusRecived;
	boost::signals2::signal<void (mw_gps*)> gpsRecived;
	boost::signals2::signal<void (mw_analog*)> analogRecived;
	boost::signals2::signal<void (mw_info*)> MWInfoRecived;
	boost::signals2::signal<void (mw_altitude*)> altitudeRecived;
	boost::signals2::signal<void (mw_attitude*)> attitudeRecived;
	boost::signals2::signal<void (char msp_cmd)> answer;
	boost::signals2::signal<void (char msp_cmd)> UnsupportedCmd;
	boost::signals2::signal<void (std::string)> error;

protected:
	void sendRequest(unsigned char requestCode);

private:
    mw_metric   _metricData;
	mw_status   _statusData;
	mw_analog   _analogData;
	mw_gps      _gpsData;
	mw_info     _infoData;
	mw_altitude _altitudeData;
	mw_attitude _attitudeData;

	void read(char * inData, int byteToRead); // Parse the input data then call detect()
	void detect(char *command); // Parse the input command then call some virtual function.
	void disconnectEvent(std::string err); //Re implement method of error notify
};


#endif /* COPTER_MWIFACE_MULTIWII_H_ */
