#include "Arm.h"

Arm::Arm()
{
	
}

void Arm::begin(Servo& _fist, Servo& _wrist, Motor& _pinion, DigitalDevice& _lowSwitch, DigitalDevice& _highSwitch)
{
	fist = _fist;
	wrist = _wrist;
	pinion = _pinion;
	lowSwitch = _lowSwitch;
	highSwitch = _highSwitch;
}

void Arm::moveFist(int length)
{
	fist.write(length);
}

void Arm::moveWrist(int length)
{
	wrist.write(length);
}

/*	
 *	Returns 0 or 1 for switch is at bottom or top respectively OR -1 when in between
 *	
 *	Takes 0 or 1 for switch should be at bottom or top respectively 
 */
int Arm::movePinion(int switchEnd) // Using limit switches
{
	if (switchEnd == 1)
	{
		if (highSwitch.read() == HIGH)
		{
			return 1;
		}
		else
		{
			pinion.output(1);
			return -1;
		}
	}
	
	if (switchEnd == 0)
	{
		if (lowSwitch.read() == HIGH)
		{
			return 0;
		}
		else
		{
			pinion.output(-1);
			return -1;
		}
	}
}