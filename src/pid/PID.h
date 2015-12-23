#ifndef PID_v1_h
#define PID_v1_h
#define LIBRARY_VERSION	1.1.1

#include <stdint.h>

class PID
{
public:

	//Constants used in some of the functions below
	//#define AUTOMATIC	1
	//#define MANUAL	0
	enum Direction
	{
		DIRECT, REVERSE
	};

	//commonly used functions **************************************************************************
	PID(double & Input, double & Output, double & Setpoint, double Kp, double Ki,
			double Kd, Direction ControllerDirection);

	//void SetMode(int Mode);   // * sets PID to either Manual (0) or Auto (non-0)

	void Compute(); // * performs the PID calculation.  it should be
	//   called every time loop() cycles. ON/OFF and
	//   calculation frequency can be set using SetMode
	//   SetSampleTime respectively

	void SetOutputLimits(double min, double max); //clamps the output to a specific range. 0-255 by default, but
	//it's likely the user will want to change this depending on
	//the application

	//available but not commonly used functions ********************************************************
	void SetTunings(double Kp, double Ki, double Kd); //   constructor, this function gives the user the option
	//   of changing tunings during runtime for Adaptive control
	void SetControllerDirection(Direction direction);// * Sets the Direction, or "Action" of the controller. DIRECT
	//   means the output will increase when error is positive. REVERSE
	//   means the opposite.

	//Display functions ****************************************************************
	double GetKp();			// These functions query the pid for interal values.
	double GetKi();			//  they were created mainly for the pid front-end,
	double GetKd();			// where it's important to know what is actually
	Direction GetDirection();

	uint64_t GetTimeStampMicros();

private:
	void Initialize();

	double _kp;                  // * (P)roportional Tuning Parameter
	double _ki;                  // * (I)ntegral Tuning Parameter
	double _kd;                  // * (D)erivative Tuning Parameter

	Direction _controllerDirection;

	double *_input;  // * Pointers to the Input, Output, and Setpoint variables
	double *_output; //   This creates a hard link between the variables and the
	double *_setPoint; //   PID, freeing the user from having to constantly tell us
	//   what these values are.  with pointers we'll just know.

	uint64_t _lastTime;
	double _ITerm, _lastInput;


	double _outMin, _outMax;
	bool _limitEnable;
};
#endif

