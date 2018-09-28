#include "StepperMotorDrivetrain.h"
#include <String.h>

//constructor
StepperMotorDrivetrain::StepperMotorDrivetrain()
{
	//sets steps and step counter to 0
	this->frontLeftSteps = 0;
	this->frontLeftCounter = 0;
	
	this->backLeftSteps = 0;
	this->backLeftCounter = 0;
	
	this->frontRightSteps = 0;
	this->frontRightCounter = 0;
	
	this->backRightSteps = 0;
	this->backRightCounter = 0;
	
	//Set this to a medium speed
	this->rpm = 25;
}

//operator overload?
void StepperMotorDrivetrain::operator=(const StepperMotorDrivetrain& drivetrain)
{
	//sets private variables from each drivetrain equal to one other
	this->fLeftIN1 = drivetrain.fLeftIN1;
	this->fLeftIN2 = drivetrain.fLeftIN2;
	this->fLeftIN3 = drivetrain.fLeftIN3;
	this->fLeftIN4 = drivetrain.fLeftIN4;
	
	this->bLeftIN1 = drivetrain.bLeftIN1;
	this->bLeftIN2 = drivetrain.bLeftIN2;
	this->bLeftIN3 = drivetrain.bLeftIN3;
	this->bLeftIN4 = drivetrain.bLeftIN4;
	
	this->fRightIN1 = drivetrain.fRightIN1;
	this->fRightIN2 = drivetrain.fRightIN2;
	this->fRightIN3 = drivetrain.fRightIN3;
	this->fRightIN4 = drivetrain.fRightIN4;
	
	this->bRightIN1 = drivetrain.bRightIN1;
	this->bRightIN2 = drivetrain.bRightIN2;
	this->bRightIN3 = drivetrain.bRightIN3;
	this->bRightIN4 = drivetrain.bRightIN4;
	
	this->rpm = drivetrain.rpm;
	
	this->frontLeftSteps = drivetrain.frontLeftSteps;
	this->backLeftSteps = drivetrain.backLeftSteps;
	this->frontRightSteps = drivetrain.frontRightSteps;
	this->backRightSteps = drivetrain.backRightSteps;

	this->frontLeftCounter = drivetrain.frontLeftCounter;
	this->backLeftCounter = drivetrain.backLeftCounter;
	this->frontRightCounter = drivetrain.frontRightCounter;
	this->backRightCounter = drivetrain.backRightCounter;
}

//sets pins for front left motors
void StepperMotorDrivetrain::initFrontLeft(int in1, int in2, int in3, int in4)
{
	this->fLeftIN1 = in1;
	this->fLeftIN2 = in2;
	this->fLeftIN3 = in3;
	this->fLeftIN4 = in4;
	
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
}

//sets pins for back left motors
void StepperMotorDrivetrain::initBackLeft(int in1, int in2, int in3, int in4)
{
	this->bLeftIN1 = in1;
	this->bLeftIN2 = in2;
	this->bLeftIN3 = in3;
	this->bLeftIN4 = in4;
	
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
}

//sets pins for front right motors
void StepperMotorDrivetrain::initFrontRight(int in1, int in2, int in3, int in4)
{
	this->fRightIN1 = in1;
	this->fRightIN2 = in2;
	this->fRightIN3 = in3;
	this->fRightIN4 = in4;
	
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
}

//sets pins for back right motors
void StepperMotorDrivetrain::initRight(int in1, int in2, int in3, int in4)
{
	this->bRightIN1 = in1;
	this->bRightIN2 = in2;
	this->bRightIN3 = in3;
	this->bRightIN4 = in4;
	
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
}

//sets speed of drivetrain
void StepperMotorDrivetrain::setRPM(float speed)
{
	this->rpm = abs(speed);
}

//moves the drivetrain
void StepperMotorDrivetrain::step(int left, int right)
{
	bool millisecond_interval = false;
	
	//We basically force left and right to be equal here, because they should be.
	//NO CURVE TURNS ALLOWED (Down with tank steer)
	int steps = min(abs(left), abs(right));
	
	int leftDirection = left < 0 ? -1 : 1;
	int rightDirection = right < 0 ? -1 : 1;
	
	//Determine how many microseconds we want to wait, and convert to an integer
	double totalTime = (static_cast<double>(steps) / STEPS_PER_REVOLUTION) / this->rpm * 60.0 * 1000.0 * 1000.0;
	double T = (totalTime / steps) / 2;
	
	//Convert to milliseconds if delay would be greater than 5,000 us.
	if(T > 5000)
	{
		T /= 1000;
		millisecond_interval = true;
	}
	
	unsigned long stepWait = static_cast<int>(T);
	
	for(int i = 0; i < steps; ++i)
	{
		this->leftSteps += leftDirection;
		this->rightSteps += rightDirection;
		
		this->leftCounter += leftDirection;
		this->rightCounter += rightDirection;
		
		//Constrain the counters to the step boundaries
		//Left
		this->leftCounter = this->leftCounter < 0 ? STEPS_PER_REVOLUTION - 1 : this->leftCounter;
		this->leftCounter = this->leftCounter >= STEPS_PER_REVOLUTION ? 0 : this->leftCounter;
		//Right
		this->rightCounter = this->rightCounter < 0 ? STEPS_PER_REVOLUTION - 1 : this->rightCounter;
		this->rightCounter = this->rightCounter >= STEPS_PER_REVOLUTION ? 0 : this->rightCounter;

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

//resets the step counters to 0
void StepperMotorDrivetrain::resetStepCounter()
{
	leftSteps = 0;
	rightSteps = 0;
}

//getter method for left motor steps
long StepperMotorDrivetrain::getFrontLeftSteps()
{
	return this->frontLeftSteps;
}

//getter method for left motor steps
long StepperMotorDrivetrain::getBackLeftSteps()
{
	return this->backLeftSteps;
}

//getter method for right motor steps
long StepperMotorDrivetrain::getFrontRightSteps()
{
	return this->frontRightSteps;
}

//getter method for right motor steps
long StepperMotorDrivetrain::getBackRightSteps()
{
	return this->backRightSteps;
}

//helper method to convert inches to steps
int StepperMotorDrivetrain::convertInchesToSteps(float inches)
{
	//number of steps / circumference of wheel = ratio
	return static_cast<int>((STEPS_PER_REVOLUTION/(2.875*3.141592653589))*inches);
}

//Private Functions

void StepperMotorDrivetrain::singleStep(unsigned int stepWait)
{
	sendStepSignalToLeft(leftCounter % 4);
	sendStepSignalToRight(rightCounter % 4);
    delay(stepWait); // Wait
}

//same as above but with a different delay function
void StepperMotorDrivetrain::singleStep_us(unsigned int stepWait)
{
	sendStepSignalToFrontLeft(leftCounter % 4);
	sendStepSignalToRight(rightCounter % 4);
    delayMicroseconds(stepWait); // Wait
}

void StepperMotorDrivetrain::sendStepSignalToFrontLeft(int stepID)
{
	switch (stepID) {
		case 0:  // 1010
			digitalWrite(fLeftIN1, HIGH);
			digitalWrite(fLeftIN2, LOW);
			digitalWrite(fLeftIN3, HIGH);
			digitalWrite(fLeftIN4, LOW);
			break;
		case 1:  // 0110
			digitalWrite(fLeftIN1, LOW);
			digitalWrite(fLeftIN2, HIGH);
			digitalWrite(fLeftIN3, HIGH);
			digitalWrite(fLeftIN4, LOW);
			break;
		case 2:  //0101
			digitalWrite(fLeftIN1, LOW);
			digitalWrite(fLeftIN2, HIGH);
			digitalWrite(fLeftIN3, LOW);
			digitalWrite(fLeftIN4, HIGH);
			break;
		case 3:  //1001
			digitalWrite(fLeftIN1, HIGH);
			digitalWrite(fLeftIN2, LOW);
			digitalWrite(fLeftIN3, LOW);
			digitalWrite(fLeftIN4, HIGH);
			break;
    }
}

void StepperMotorDrivetrain::sendStepSignalToBackLeft(int stepID)
{
	switch (stepID) {
		case 0:  // 1010
			digitalWrite(bLeftIN1, HIGH);
			digitalWrite(bLeftIN2, LOW);
			digitalWrite(bLeftIN3, HIGH);
			digitalWrite(bLeftIN4, LOW);
			break;
		case 1:  // 0110
			digitalWrite(bLeftIN1, LOW);
			digitalWrite(bLeftIN2, HIGH);
			digitalWrite(bLeftIN3, HIGH);
			digitalWrite(bLeftIN4, LOW);
			break;
		case 2:  //0101
			digitalWrite(bLeftIN1, LOW);
			digitalWrite(bLeftIN2, HIGH);
			digitalWrite(bLeftIN3, LOW);
			digitalWrite(bLeftIN4, HIGH);
			break;
		case 3:  //1001
			digitalWrite(bLeftIN1, HIGH);
			digitalWrite(bLeftIN2, LOW);
			digitalWrite(bLeftIN3, LOW);
			digitalWrite(bLeftIN4, HIGH);
			break;
    }
}

void StepperMotorDrivetrain::sendStepSignalToFrontRight(int stepID)
{
	switch (stepID) {
		case 0:  // 1010
			digitalWrite(fRightIN1, HIGH);
			digitalWrite(fRightIN2, LOW);
			digitalWrite(fRightIN3, HIGH);
			digitalWrite(fRightIN4, LOW);
			break;
		case 1:  // 0110
			digitalWrite(fRightIN1, LOW);
			digitalWrite(fRightIN2, HIGH);
			digitalWrite(fRightIN3, HIGH);
			digitalWrite(fRightIN4, LOW);
			break;
		case 2:  //0101
			digitalWrite(fRightIN1, LOW);
			digitalWrite(fRightIN2, HIGH);
			digitalWrite(fRightIN3, LOW);
			digitalWrite(fRightIN4, HIGH);
			break;
		case 3:  //1001
			digitalWrite(fRightIN1, HIGH);
			digitalWrite(fRightIN2, LOW);
			digitalWrite(fRightIN3, LOW);
			digitalWrite(fRightIN4, HIGH);
			break;
    }
}

void StepperMotorDrivetrain::sendStepSignalToBackRight(int stepID)
{
	switch (stepID) {
		case 0:  // 1010
			digitalWrite(bRightIN1, HIGH);
			digitalWrite(bRightIN2, LOW);
			digitalWrite(bRightIN3, HIGH);
			digitalWrite(bRightIN4, LOW);
			break;
		case 1:  // 0110
			digitalWrite(bRightIN1, LOW);
			digitalWrite(bRightIN2, HIGH);
			digitalWrite(bRightIN3, HIGH);
			digitalWrite(rightIN4, LOW);
			break;
		case 2:  //0101
			digitalWrite(bRightIN1, LOW);
			digitalWrite(bRightIN2, HIGH);
			digitalWrite(bRightIN3, LOW);
			digitalWrite(bRightIN4, HIGH);
			break;
		case 3:  //1001
			digitalWrite(bRightIN1, HIGH);
			digitalWrite(bRightIN2, LOW);
			digitalWrite(bRightIN3, LOW);
			digitalWrite(bRightIN4, HIGH);
			break;
    }
}
//Pass String for direction "forward diagnal left", "backward diagnal left", "forward diagnal right", "backward diagnal right", "left", "right".
void StepperMotorDrivetrain::strafe(string direction, unsigned int distance){


	switch(direction){
		case("left"):
			for(int i = 0; i < distance; i++){
				rightBackStep -= 1;
				rightFrontStep += 1;
				leftBackStep += 1;
				leftFrontStep -= 1;
				sendSteplSignalToBackRight(rightBackStep % 4);
				sendStepSignalToFrontRight(rightFrontStep % 4);
				sendStepSignalToBackLeft(leftBackStep % 4);
				SendStepSignalToFrontLeft(leftFrontStep % 4);
			}
			break;
		case("right"):
			for(int i = 0; i < distance; i++){
				rightBackStep += 1;
				rightFrontStep -= 1;
				leftBackStep -= 1;
				leftFrontStep += 1;
				sendSteplSignalToBackRight(rightBackStep % 4);
				sendStepSignalToFrontRight(rightFrontStep % 4);
				sendStepSignalToBackLeft(leftBackStep % 4);
				sendStepSignalToFrontLeft(leftFrontStep % 4);
			}
			break;
		case("forward diagnal left"):
			for(int i = 0; i < distance; i++){
				leftFrontStep += 1;
				rightBackStep += 1;
				sendStepSignalToFrontLeft(leftFrontStep % 4);
				sendSteplSignalToBackRight(leftBackStep % 4);
			}
			break;
		case("backward diagnol left"):
			for(int i = 0; i < distance; i++){
				leftFrontStep -= 1;
				rightBackStep -= 1;
				sendStepSignalToFrontLeft(leftFrontStep % 4);
				sendSteplSignalToBackRight(leftBackStep % 4);
			}
			break;
		case("forward diagnol right"):
			for(int i = 0; i < distance; i++){
				leftBackStep += 1;
				rightFrontStep += 1;
				sendStepSignalToBackLeft(leftBackStep % 4);
				sendSteplSignalToFrontRight(leftFrontStep % 4);
			}
			break;
		case("backward diagnol right"):
			for(int i = 0; i < distance; i++){
				leftBackStep -= 1;
				rightFrontStep -= 1;
				sendStepSignalToBackLeft(leftBackStep % 4);
				sendSteplSignalToFrontRight(leftFrontStep % 4);
			}
	}
}