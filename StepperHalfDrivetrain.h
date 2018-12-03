#ifndef STEPPERHALFDRIVETRAIN_H
#define STEPPERHALFDRIVETRAIN_H

#include <Arduino.h>
#include <String.h>

#define STEPS_PER_REVOLUTION 200

/*
 * (Taken from Arduino Stepper.h)
 * Run through sequence to make a step
 * The sequence of control signals for 4 control wires is as follows:
 *
 * Step C0 C1 C2 C3
 *    1  1  0  1  0
 *    2  0  1  1  0
 *    3  0  1  0  1
 *    4  1  0  0  1
 */

class StepperHalfDrivetrain
{
	public:
		StepperHalfDrivetrain();
		
		//TODO: reorder the methods in cpp to match this order
		void operator=(const StepperMotorDrivetrain& drivetrain);
		
		//initialize motors
		void initFront(int in1, int in2, int in3, int in4);
		void initBack(int in1, int in2, int in3, int in4);
		
		//movement
		void step(int steps);
				
		//setters and resetters
		void setRPM(float speed);
		void resetStepCounter();
		
		//getters
		long getFrontSteps();
		long getBackSteps();
		
		//helpers
		double calculateStepWait(int steps);
		int convertInchesToSteps(float inches);
		
	private:
		//Front Motor
		int frontIN1, frontIN2, frontIN3, frontIN4;
		
		//Back Motor
		int backIN1, backIN2, backIN3, backIN4;
		
		//RPM of all drive motors
		float rpm;
		
		//Step counters
		long frontSteps;
		long backSteps;
		
		int frontCounter, backCounter;
		
		//Stepping functions
		void singleStep(unsigned int stepWait);
		void singleStep_us(unsigned int stepWait);
		
		void sendStepSignalToFront(int stepID);
		void sendStepSignalToBack(int stepID);
		bool inRange(float variable, float constant, float range);

};

#endif