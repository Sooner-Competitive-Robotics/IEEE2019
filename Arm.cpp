#include "Arm.h"

Arm::Arm()
{
	
}

Arm::Arm(Servo _claw, Servo _rotator, Motor _pinion)
{
	claw = _claw;
	rotator = _rotator;
	pinion = _pinion;
}

void Arm::moveClaw(int length)
{
	claw.write(length);
}

void Arm::moveRotator(length)
{
	rotator.write(length);
}

void Arm::movePinion // Using linit switches probably
{
	pinion.output();
}