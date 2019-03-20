#include "Arm.h"

/* initial position of arm:
 * pinion is fully retracted
 * fist is closedir
 * wrist is bent (claw is down)
 */
 
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

//reset arm to initial positions
void Arm::reset()
{
	fist.write(0 - fistAngle);
	wrist.write(0 - wristAngle);
	movePinion(-1);
	
	fistAngle = 0;
	wristAngle = 0;
}

//TODO: test angles for open and close and put in Globals
void Arm::moveFist(int angle)
{
	fist.write(angle);
	fistAngle += angle;
}

//TODO: test angles for up and down and put in Globals
void Arm::moveWrist(int angle)
{
	wrist.write(angle);
	wristAngle += angle;
}

/*	
 *	Returns -1 or 1 for switch is retracted or extended respectively OR 0 when in between (moving)
 *	
 *	Takes -1 or 1 for switch should be at retracted or extended respectively 
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
			return 0;
		}
	}
	
	if (switchEnd == -1)
	{
		if (lowSwitch.read() == HIGH)
		{
			return -1;
		}
		else
		{
			pinion.output(-1);
			return 0;
		}
	}
}

// Returns -1 or 1 for switch is retracted or extended respectively OR 0 when neither
int Arm::getPinionPos()
{
	if (highSwitch.read() == HIGH)
	{
		return 1;
	}
	else if (lowSwitch.read() == HIGH)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int Arm::getFistAngle()
{
	return fistAngle;
}

int Arm::getWristAngle()
{
	return wristAngle;
}



