#ifndef PPM_H
#define PPM_H

#include "../BoostSerialPort/BSerialPort.h"
#include <list>
#include <functional>

#define THR_CH 3
#define YAW_CH 4
#define ROLL_CH 2
#define PITH_CH 1

class RC
{
public:
	RC();
	RC(uint8_t channel, uint16_t value);

	uint8_t channel() const;
	void setChannel(const uint8_t &channel);
	uint16_t value() const;
	void setValue(const uint16_t &value);
	void *operator ()(uint8_t channel, uint16_t value);
private:

	uint8_t _channel;
	uint16_t _value;
};

class PPM: public BSerialPort
{
public:
	PPM();

	std::function<void(const std::list<RC> & control)> controlData;
	std::function<void(const std::list<RC> & control)> additionalData;
	std::function<void(const RC &)> rawDataResived;

private:
	void read(const uint8_t *inData, int byteToRead);
	void dataParse(const RC & data);
	RC _rcTemp;

	std::list<RC> _control;
	std::list<RC> _additional;
};

#endif // PPM_H
