#ifndef ARM_H
#define ARM_H

#include <Servo.h>
#include "Motor.h"
#include "DigitalDevice.h"

class Arm
{
	public:
	
		Arm();

		void begin(Servo& _fist, Servo& _wrist, Motor& _pinion, DigitalDevice& _lowSwitch, DigitalDevice& _highSwitch);
	
		void moveFist(int length);
		
		void moveWrist(int length);
		
		int movePinion(int switchEnd); // Using limit switches probably
		
	private:
		
		Servo fist;
		
		Servo wrist;
		
		Motor pinion;
		
		DigitalDevice lowSwitch;
		DigitalDevice highSwitch;
	
}

#endif