#ifndef INTAKE_H
#define INTAKE_H

#include <Arduino.h>
#include <Servo.h>


class Intake
{
	public:
		Intake();
		
		void begin(Motor& motor, Encoder& encoder, DigitalDevice& loLimitSwitch, DigitalDevice& hiLimitSwitch, Claw& claw);
		
		void pickUp();
		
		void dropOff();
		
		Motor getRackAndPinionMotor();
		
		Encoder& getRackAndPinionEncoder();
		
		void extendRackAndPinion();
		
		Claw claw;
		
		void extendLimit();
		void retractLimit();
		void reset();
			
	private:
		enum PickUpState{IDLE, GRAB, RAISE, DROP};
		enum DropOffState{IDLEd, GRABd, RAISEd, DROPd};
	
		int lastHeight;
	
		String state;
		
		float currentMotorOutput;
	
		float coerce(float value, float high, float low);
	
		PickUpState pickUpState;
		DropOffState dropOffState;
		PIDController intakePID;
	
		Motor intakeMotor;
	
		DigitalDevice lowLimitSwitch;
		DigitalDevice highLimitSwitch;
					
		int intakeReturn;
};

#endif
