#include "StepperHalfDrivetrain.h"
#include <String.h>

StepperHalfDrivetrain::StepperHalfDrivetrain() 
{
	this->frontSteps = 0;
	this->frontCounter = 0;
	
	this->backSteps = 0;
	this->backCounter = 0;
	
	this->rpm = 25;
}

void StepperHalfDrivetrain::operator=(const StepperHalfDrivetrain& drivetrain) 
{
	this->frontIN1 = drivetrain.frontIN1;
	this->frontIN2 = drivetrain.frontIN2;
	this->frontIN3 = drivetrain.frontIN3;
	this->frontIN4 = drivetrain.frontIN4;
	
	this->backIN1 = drivetrain.backIN1;
	this->backIN2 = drivetrain.backIN2;
	this->backIN3 = drivetrain.backIN3;
	this->backIN4 = drivetrain.backIN4;
	
	this->rpm = drivetrain.rpm;
	
	this->frontCounter = drivetrain.frontCounter;
	this->backCounter = drivetrain.backCounter;
}

void StepperHalfDrivetrain::initFront(int in1, int in2, int in3, int in4) 
{
	this->frontIN1 = in1;
	this->frontIN2 = in2;
	this->frontIN3 = in3;
	this->frontIN4 = in4;
	
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
}

void StepperHalfDrivetrain::initBack(int in1, int in2, int in3, int in4) 
{
	this->backIN1 = in1;
	this->backIN2 = in2;
	this->backIN3 = in3;
	this->backIN4 = in4;
	
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
}

// Moves the drivetrain
void StepperMotorDrivetrain::step(int front, int back)
{
	bool millisecond_interval = false;
	int actSteps = max(abs(front), abs(back));
	
	int frontDirection = frontSteps < 0 ? -1 : 1;
	int backDirection = backSteps < 0 ? -1 : 1;
	
	//Determine how many microseconds we want to wait, and convert to an integer
	//double totalTime = (static_cast<double>(steps) / STEPS_PER_REVOLUTION) / this->rpm * 60.0 * 1000.0 * 1000.0;
	double T = calculateStepWait(actSteps);
	
	//Convert to milliseconds if delay would be greater than 5,000 us.
	if(T > 5000)
	{
		T /= 1000;
		millisecond_interval = true;
	}
	
	unsigned long stepWait = static_cast<int>(T);
	
	for(int i = 0; i < actSteps; ++i)
	{
		this->frontSteps += frontDirection;
		this->backSteps += backDirection;
		
		this->frontCounter += frontDirection;
		this->backCounter += backDirection;
		
		//Constrain the counters to the step boundaries
		//Front
		this->frontCounter = this->frontCounter < 0 ? STEPS_PER_REVOLUTION - 1 : this->frontCounter;
		this->frontCounter = this->frontCounter >= STEPS_PER_REVOLUTION ? 0 : this->frontCounter;
		//Back
		this->backCounter = this->backCounter < 0 ? STEPS_PER_REVOLUTION - 1 : this->backCounter;
		this->backCounter = this->backCounter >= STEPS_PER_REVOLUTION ? 0 : this->backCounter;

		if(millisecond_interval)
		{
			singleStep(stepWait);
		}
		else
		{
			singleStep_us(stepWait);
		}
	}
}


//calculate the amount of time the amount of steps will take
double StepperMotorDrivetrain::calculateStepWait(int steps) 
{

	//Determine how many microseconds we want to wait, and convert to an integer	
	double totalTime = (static_cast<double>(steps) / STEPS_PER_REVOLUTION) / this->rpm * 60.0 * 1000.0 * 1000.0;
	double T = (totalTime / steps) / 2;
	
	return T;
}

void StepperHalfDrivetrain::setRPM(float speed) 
{
	this->rpm = abs(speed);
}

void StepperMotorDrivetrain::sendStepSignalToFront(int stepID)
{
	switch (stepID) {
		case 0:  // 1010
			digitalWrite(frontIN1, HIGH);
			digitalWrite(frontIN2, LOW);
			digitalWrite(frontIN3, HIGH);
			digitalWrite(frontIN4, LOW);
			break;
		case 1:  // 0110
			digitalWrite(frontIN1, LOW);
			digitalWrite(frontIN2, HIGH);
			digitalWrite(frontIN3, HIGH);
			digitalWrite(frontIN4, LOW);
			break;
		case 2:  //0101
			digitalWrite(frontIN1, LOW);
			digitalWrite(frontIN2, HIGH);
			digitalWrite(frontIN3, LOW);
			digitalWrite(frontIN4, HIGH);
			break;
		case 3:  //1001
			digitalWrite(frontIN1, HIGH);
			digitalWrite(frontIN2, LOW);
			digitalWrite(frontIN3, LOW);
			digitalWrite(frontIN4, HIGH);
			break;
    }
}

void StepperMotorDrivetrain::sendStepSignalToBack(int stepID)
{
	switch (stepID) 
	{
		case 0:  // 1010
			digitalWrite(backIN1, HIGH);
			digitalWrite(backIN2, LOW);
			digitalWrite(backIN3, HIGH);
			digitalWrite(backIN4, LOW);
			break;
		case 1:  // 0110
			digitalWrite(backIN1, LOW);
			digitalWrite(backIN2, HIGH);
			digitalWrite(backIN3, HIGH);
			digitalWrite(backIN4, LOW);
			break;
		case 2:  //0101
			digitalWrite(backIN1, LOW);
			digitalWrite(backIN2, HIGH);
			digitalWrite(backIN3, LOW);
			digitalWrite(backIN4, HIGH);
			break;
		case 3:  //1001
			digitalWrite(backIN1, HIGH);
			digitalWrite(backIN2, LOW);
			digitalWrite(backIN3, LOW);
			digitalWrite(backIN4, HIGH);
			break;
    }
}

	
	