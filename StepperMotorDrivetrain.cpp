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
void StepperMotorDrivetrain::initBackRight(int in1, int in2, int in3, int in4)
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
	double T = calculateStepWait(steps);
	
	//Convert to milliseconds if delay would be greater than 5,000 us.
	if(T > 5000)
	{
		T /= 1000;
		millisecond_interval = true;
	}
	
	unsigned long stepWait = static_cast<int>(T);
	
	for(int i = 0; i < steps; ++i)
	{
		this->frontLeftSteps += leftDirection;
		this->backLeftSteps += leftDirection;
		this->frontRightSteps += rightDirection;
		this->backRightSteps += rightDirection;
		
		this->frontLeftCounter += leftDirection;
		this->backLeftCounter += leftDirection;
		this->frontRightCounter += rightDirection;
		this->backRightCounter += rightDirection;
		
		//Constrain the counters to the step boundaries
		//Left
		this->frontLeftCounter = this->frontLeftCounter < 0 ? STEPS_PER_REVOLUTION - 1 : this->frontLeftCounter;
		this->frontLeftCounter = this->frontLeftCounter >= STEPS_PER_REVOLUTION ? 0 : this->frontLeftCounter;
		this->backLeftCounter = this->backLeftCounter < 0 ? STEPS_PER_REVOLUTION - 1 : this->backLeftCounter;
		this->backLeftCounter = this->backLeftCounter >= STEPS_PER_REVOLUTION ? 0 : this->backLeftCounter;
		//Right
		this->frontRightCounter = this->frontRightCounter < 0 ? STEPS_PER_REVOLUTION - 1 : this->frontRightCounter;
		this->frontRightCounter = this->frontRightCounter >= STEPS_PER_REVOLUTION ? 0 : this->frontRightCounter;
		this->backRightCounter = this->backRightCounter < 0 ? STEPS_PER_REVOLUTION - 1 : this->backRightCounter;
		this->backRightCounter = this->backRightCounter >= STEPS_PER_REVOLUTION ? 0 : this->backRightCounter;

		if(millisecond_interval)
		{
			singleStep(1, 0, stepWait);
		}
		else
		{
			singleStep_us(1, 0, stepWait);
		}
	}
}

//calculate the amount of time the amount of steps will take
double StepperMotorDrivetrain::calculateStepWait(int steps) {

	//Determine how many microseconds we want to wait, and convert to an integer	
	double totalTime = (static_cast<double>(steps) / STEPS_PER_REVOLUTION) / this->rpm * 60.0 * 1000.0 * 1000.0;
	double T = (totalTime / steps) / 2;
	
	
	return T;
}

//resets the step counters to 0
void StepperMotorDrivetrain::resetStepCounter()
{
	frontLeftSteps = 0;
	frontRightSteps = 0;
	backLeftSteps = 0;
	backRightSteps = 0;
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
void StepperMotorDrivetrain::singleStep(int forwardDirection, int sidewayDirection, unsigned int stepWait)
{
	if((forwardDirection != 0 && sidewayDirection == 0 )||(forwardDirection == 0 && sidewayDirection != 0)) 
	{	
		sendStepSignalToFrontLeft(frontLeftCounter % 4);
		sendStepSignalToFrontRight(frontRightCounter % 4);
		sendStepSignalToBackLeft(backLeftCounter % 4);
		sendStepSignalToBackRight(backRightCounter % 4);
	}
	
	else if(forwardDirection != 0 && sidewayDirection == -1) 
	{
		sendStepSignalToFrontLeft(frontLeftSteps % 4);
		sendStepSignalToBackRight(backRightSteps % 4);
	}
	
	else if(forwardDirection != 0 && sidewayDirection == 1) 
	{
		sendStepSignalToBackLeft(frontLeftSteps % 4);
		sendStepSignalToFrontRight(backRightSteps % 4);
	}
			
	delay(stepWait); // Wait
}

//same as above but with a different delay function
void StepperMotorDrivetrain::singleStep_us(int forwardDirection, int sidewayDirection, unsigned int stepWait)
{
	if((forwardDirection != 0 && sidewayDirection == 0 )||(forwardDirection == 0 && sidewayDirection != 0))
	{
		sendStepSignalToFrontLeft(frontLeftCounter % 4);
		sendStepSignalToFrontRight(frontRightCounter % 4);
		sendStepSignalToBackLeft(backLeftCounter % 4);
		sendStepSignalToBackRight(backRightCounter % 4);
	}
	
	else if(forwardDirection != 0 && sidewayDirection == -1) 
	{
		sendStepSignalToFrontLeft(frontLeftSteps % 4);
		sendStepSignalToBackRight(backRightSteps % 4);
	}
	
	else if(forwardDirection != 0 && sidewayDirection == 1) 
	{
		sendStepSignalToBackLeft(frontLeftSteps % 4);
		sendStepSignalToFrontRight(backRightSteps % 4);
	}
	
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
			digitalWrite(bRightIN4, LOW);
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
/* Pass ints for direction
 * 
 * forwardDirection: 0-->None	1-->Forward		-1-->Backwards
 * sidewayDirection: 0-->None	1-->Right 		-1-->Left
 *
 * Use drivetrain.convertInchesToSteps(inches) in your .ino for steps
 */
void StepperMotorDrivetrain::strafe(int forwardDirection, int sidewayDirection, unsigned int stepsActual){
	
	bool millisecond_interval = false;
	
	//We basically force left and right to be equal here, because they should be.
	//NO CURVE TURNS ALLOWED (Down with tank steer)
	int steps = abs(stepsActual);
	
	double T = calculateStepWait(steps);
	
	//Convert to milliseconds if delay would be greater than 5,000 us.
	if(T > 5000)
	{
		T /= 1000;
		millisecond_interval = true;
	}
	
	unsigned long stepWait = static_cast<int>(T);
		
	// Straight Forward
	if(forwardDirection == 1 && sidewayDirection == 0)
	{
		step(steps, steps);
	}
	// Straight Backwards
	else if(forwardDirection == -1 && sidewayDirection == 0)
	{
		step(-steps, -steps);
	}
	// Left Strafe
	else if(forwardDirection == 0 && sidewayDirection == -1)
	{
		for(int i = 0; i < steps; i++)
		{
			backRightSteps -= 1;
			frontRightSteps += 1;
			backLeftSteps += 1;
			frontLeftSteps -= 1;
			if(millisecond_interval)
			{
				singleStep(0, -1, stepWait);
			}
			else
			{
				singleStep_us(0, -1, stepWait);
			}
		}
	}
	// Right Strafe
	else if(forwardDirection == 0 && sidewayDirection == 1)
	{
		for(int i = 0; i < steps; i++)
		{
			backRightSteps += 1;
			frontRightSteps -= 1;
			backLeftSteps -= 1;
			frontLeftSteps += 1;
			if(millisecond_interval)
			{
				singleStep(0, -1, stepWait);
			}
			else
			{
				singleStep_us(0, 1, stepWait);
			}
		}
	}
	// Forward Left Strafe
	else if(forwardDirection == 1 && sidewayDirection == -1)
	{
		for(int i = 0; i < steps; i++){
			frontLeftSteps += 1;
			backRightSteps += 1;
			sendStepSignalToFrontLeft(frontLeftSteps % 4);
			sendStepSignalToBackRight(backRightSteps % 4);
		}
	}
	// Backward Left Strafe 
	else if(forwardDirection == -1 && sidewayDirection == -1)
	{
		for(int i = 0; i < steps; i++)
		{
			frontLeftSteps -= 1;
			backRightSteps -= 1;
			sendStepSignalToFrontLeft(frontLeftSteps % 4);
			sendStepSignalToBackRight(backRightSteps % 4);
		}
	}
	// Forward Right Strafe
	else if(forwardDirection == 1 && sidewayDirection == 1)
	{
		for(int i = 0; i < steps; i++)
		{
			backLeftSteps += 1;
			frontRightSteps += 1;
			sendStepSignalToBackLeft(backLeftSteps % 4);
			sendStepSignalToFrontRight(frontRightSteps % 4);
		}
	}
	// Backward Right Strafe
	else if(forwardDirection == -1 && sidewayDirection == 1)
	{
		for(int i = 0; i < steps; i++)
		{
			backLeftSteps -= 1;
			frontRightSteps -= 1;
			sendStepSignalToBackLeft(backLeftSteps % 4);
			sendStepSignalToFrontRight(frontRightSteps % 4);
		}
	}
}
