#ifndef ARM_H
#define ARM_H

#include <Servo.h>
#include "Motor.h"

class Arm
{
	public:
	
		Arm();

		Arm(Servo _claw, Servo _rotator, MotorController _pinion);
	
		void moveClaw(int length);
		
		void moveRotator(int length);
		
		void movePinion(); // Using limit switches probably
		
	private:
		
		Servo claw;
		
		Servo rotator;
		
		MotorController pinion;
	
}