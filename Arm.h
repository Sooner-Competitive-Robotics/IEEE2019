#ifndef ARM_H
#define ARM_H

#include <Servo.h>
#include "Motor.h"
#include "DigitalDevice.h"

/* initial position of arm:
 * pinion is fully retracted
 * fist is closedir
 * wrist is bent (claw is down)
 */

class Arm
{
	public:
	
		Arm();

		void begin(Servo& _fist, Servo& _wrist, Motor& _pinion, DigitalDevice& _lowSwitch, DigitalDevice& _highSwitch);
	
		void reset();
		
		void moveFist(int length);
		
		void moveWrist(int length);
		
		int movePinion(int switchEnd); // Using limit switches probably
		
		int getPinionPos();
		
		int getFistAngle();
		
		int getWristAngle();
		
	private:
		
		Servo fist;
		
		Servo wrist;
		
		Motor pinion;
		
		DigitalDevice lowSwitch;
		DigitalDevice highSwitch;
		
		//angle where servos at
		int wristAngle = 0;
		int fistAngle = 0;
			
};

#endif
