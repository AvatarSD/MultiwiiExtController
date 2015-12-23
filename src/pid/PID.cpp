/**********************************************************************************************
 * Arduino PID Library - Version 1.1.1
 * by Brett Beauregard <br3ttb@gmail.com> brettbeauregard.com
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/

#include <sys/time.h>

#include "PID.h"

/*Constructor (...)*********************************************************
 *    The parameters specified here are those for for which we can't set up
 *    reliable defaults, so we need to have the user set them.
 ***************************************************************************/
PID::PID(double & input, double & output, double & setpoint, double Kp,
		double Ki, double Kd, Direction ControllerDirection) :
		_kp(Kp), _ki(Ki), _kd(Kd), _input(&input), _output(&output),
		_setPoint(&setpoint)
{
	_controllerDirection = ControllerDirection;

	_ITerm = 0;
	_outMin = 0;
	_outMax = 0;
	_limitEnable = false;

	setDirection(ControllerDirection);
	setTunings(Kp, Ki, Kd);

	_lastTime = getTimeStampMicros();							//-SampleTime;
	_lastInput = input;
}

/* Compute() **********************************************************************
 *     This, as they say, is where the magic happens.  this function should be called
 *   every time "void loop()" executes.  the function will decide for itself whether a new
 *   pid Output needs to be computed.  returns true when the output is computed,
 *   false when nothing has been done.
 **********************************************************************************/
void PID::compute()
{
	/*Snapshot*/
	double input = *_input;
	uint64_t timeNow = getTimeStampMicros();

	/*Compute all the working error variables*/
	uint64_t timeChange = timeNow - _lastTime;
	double error = *_setPoint - input;
	double inputChange = input - _lastInput;

	_ITerm += _ki * error * timeChange;
	double DTerm = (_kd * inputChange) / timeChange;

	/*Compute PID Output*/
	double output = _kp * error + _ITerm - DTerm;

	/*fix output*/
	if (_limitEnable)
	{
		if (output > _outMax)
			output = _outMax;
		else if (output < _outMin)
			output = _outMin;
	}

	/*return output*/
	*_output = output;

	/*Remember some variables for next time*/
	_lastInput = input;
	_lastTime = timeNow;

}

/* SetTunings(...)*************************************************************
 * This function allows the controller's dynamic performance to be adjusted.
 * it's called automatically from the constructor, but tunings can also
 * be adjusted on the fly during normal operation
 ******************************************************************************/
void PID::setTunings(double Kp, double Ki, double Kd)
{
	if (Kp < 0 || Ki < 0 || Kd < 0)
		return;

	_kp = Kp;
	_ki = Ki;	// * SampleTimeInSec;
	_kd = Kd;	// / SampleTimeInSec;

	setDirection(_controllerDirection);
}

/* SetOutputLimits(...)****************************************************
 *     This function will be used far more often than SetInputLimits.  while
 *  the input to the controller will generally be in the 0-1023 range (which is
 *  the default already,)  the output will be a little different.  maybe they'll
 *  be doing a time window and will need 0-8000 or something.  or maybe they'll
 *  want to clamp it from 0-125.  who knows.  at any rate, that can all be done
 *  here.
 **************************************************************************/
void PID::setOutputLimits(double Min, double Max)
{
	_limitEnable = false;
	if (Min >= Max)
		return;

	_outMin = Min;
	_outMax = Max;
	_limitEnable = true;
}

/* SetControllerDirection(...)*************************************************
 * The PID will either be connected to a DIRECT acting process (+Output leads
 * to +Input) or a REVERSE acting process(+Output leads to -Input.)  we need to
 * know which one, because otherwise we may increase the output when we should
 * be decreasing.  This is called from the constructor.
 ******************************************************************************/
void PID::setDirection(Direction direction)
{
	if (direction == Direction::REVERSE)
	{
		_kp = (0 - _kp);
		_ki = (0 - _ki);
		_kd = (0 - _kd);
	}
	_controllerDirection = direction;
}

/* Status Functions*************************************************************/
double PID::getKp()
{
	if (_controllerDirection == Direction::REVERSE)
		return (0 - _kp);
	return _kp;
}

double PID::getKi()
{
	if (_controllerDirection == Direction::REVERSE)
		return (0 - _ki);
	return _ki;
}

double PID::getKd()
{
	if (_controllerDirection == Direction::REVERSE)
		return (0 - _kd);
	return _kd;
}

PID::Direction PID::getDirection()
{
	return _controllerDirection;
}

bool PID::isLimitsON()
{
	return _limitEnable;
}

/*
 * Time in microseconds
 */
uint64_t PID::getTimeStampMicros()
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	return tv.tv_sec * (uint64_t) 1000000 + tv.tv_usec;
}
