#ifndef PID_v1_h
#define PID_v1_h
#define LIBRARY_VERSION	1.1.1

#include <stdint.h>

class PID
{
public:

	enum Direction
	{
		DIRECT, REVERSE
	};

	//commonly used functions **************************************************************************
	PID(double & Input, double & Output, double & Setpoint, double Kp,
			double Ki, double Kd, Direction ControllerDirection);

	void compute(); // * performs the PID calculation.  it should be called by timer
	void setOutputLimits(double min, double max);
	void setTunings(double Kp, double Ki, double Kd);
	void setDirection(Direction direction);
	double getIntegetPart();
	double getKp();			// These functions query the pid for interal values.
	double getKi();			//  they were created mainly for the pid front-end,
	double getKd();			// where it's important to know what is actually
	bool isLimitsON();
	Direction getDirection();

	uint64_t getTimeStampMicros();

private:
	double _kp;                  // * (P)roportional Tuning Parameter
	double _ki;                  // * (I)ntegral Tuning Parameter
	double _kd;                  // * (D)erivative Tuning Parameter

	Direction _controllerDirection;

	double *_input;  // * Pointers to the Input, Output, and Setpoint variables
	double *_output; //   This creates a hard link between the variables and the
	double *_setPoint; //   PID, freeing the user from having to constantly tell us

	uint64_t _lastTime;
	double _ITerm, _lastInput;

	double _outMin, _outMax;
	bool _limitEnable;
};
#endif

