#include "Intake.h"

Intake::Intake()
{
	this->currentMotorOutput = 0;
	
	intakePID.initialize(0, intakeKp, intakeKi, intakeKd);
}

void Intake::begin(Motor& motor, /*Encoder& encoder*/, DigitalDevice& loLimitSwitch, DigitalDevice& hiLimitSwitch, Claw claw)
{
	this->intakeMotor = motor;
	//this->intakeEncoder = encoder;
	this->lowLimitSwitch = loLimitSwitch;
	this->highLimitSwitch = hiLimitSwitch;
	this->claw = claw;
	
	this->pickUpState = IDLE;
	this->dropOffState = IDLEd;
	
	//this->intakeEncoder.reset();
}

/*
int Intake::pickUp()
{
	claw.drop();
	claw.close();
	claw.raise();
		
	return 1;
}

//location: if block needs to be dropped on other side or on same side of mothership
void Intake::dropOff(int location)
{	
	if location == 0
	{
		this->claw.drop();
		this->claw.open();
		this->claw.raise();
	}
	else
	{
		this->extend();
		this->claw->drop();
		this->claw.open();
		this->claw.raise();
	}
}
*/
void Intake::extend()



void Intake::pickUpSequence()
{	
	switch(this->pickUpState)
	{
		case IDLE:
			this->state = "IDLE";
			currentMotorOutput = resetSpeed;
		
			//If the intake is above the grab height, drop the magnet to that height
			if(this->lowLimitSwitch.read() != HIGH) // This MUST bottom out!
			{
				//Output <0 to go down
				this->intakeMotor.output(-motorSpeed);
			}
			else //Otherwise it is time to grab the coin
			{
				//this->intakeEncoder.reset();
				this->intakeMotor.output(0);
				this->state = "GRAB";
				this->pickUpState = GRAB;
			}
			this->intakeReturn = 0;
			
		case GRAB:
			//this->intakeEncoder.reset();
			this->state = "GRAB";
			//Stop the motor so we can do a pickup
			this->intakeMotor.output(stallSpeed);
			
			//Drop claw down
			this->claw.drop();
			
			//Wait to make sure it dropped
			//TODO: Define clawDropTime
			delay(clawDropTime);
			
			//Pick up the coin
			this->claw.grab();
			
			//Wait to make sure it dropped
			//TODO: Define clawGrabTime
			delay(clawGrabTime);
			
			//Raise claw
			this->claw.raise();
			
			//Wait to make sure claw is raised
			//TODO: Define clawRaiseTime (probably same as claw drop time)
			delay(clawRaiseTime);
			
			this->state = "IDLE";
			this->pickUpState = IDLE;
			
			//Process is complete yet
			this->intakeReturn = 1;
			
		default:
			this->state = "IDLE";
			this->pickUpState = IDLE;
			this->intakeReturn = 0;
	}
	
}

//takes in if location is on same side of mothership as robot or not
//initiates after robot is optimum position to drop
void Intake::dropOffSequence(bool location)
{
	
	switch(this->dropOffState)
	{
		case IDLEd:
		
			//if claw is not in up position, it should be
			if (this->claw.position() != "UP")
			{
				this->claw.raise();
			}
			
			//de-extend if not
			while (this->loLimitSwitch != HIGH)
			{
				//Output <0 to go back (in)
				this->intakeMotor.output(-motorSpeed);
			}
			
			//Otherwise it is time to grab the coin from storage
			this->dropOffState = DROPd;
				
		case DROPd:
			
			if (location)
			{
				//Open claw
				this->claw.open();
				
				break;
			}
			else 
			{
				//extend
				while (this->hiLimitSwitch != HIGH)
				{
					//Output >0 to go out
					this->intakeMotor.output(motorSpeed);
				}
				
				//drop block
				this->claw.open();
				
				//wait to make sure claw is open
				delay(clawOpenTime);

				break;
			}
			
			//set the sequence to idle
			this->dropOffState = IDLEd;
			
		default:
			this->dropOffState = IDLEd;
	}
	
}

/*
void Intake::extendRackAndPinion(int newHeight)
{
	while (abs(this->intakeEncoder.getValue() - newHeight) > heightThreshold)
	{
		//If we are above the last height lower the motor
		if(lastHeight > newHeight)
		{
			this->intakeMotor.output((-1) * (motorSpeed));
		}
		//If we are below the last height raise the motor
		else if(lastHeight < newHeight)
		{
			this->intakeMotor.output((1) * (motorSpeed));
		}
	}
	if (abs(this->intakeEncoder.getValue() - newHeight) < heightThreshold)
	{
		lastHeight = newHeight;
	}
}
*/

Motor Intake::getRackAndPinionMotor()
{
	return this->intakeMotor;
}

/*
Encoder& Intake::getRackAndPinionEncoder()
{
	//Serial.print(intakeEncoder.getA());
	return this->intakeEncoder;
}
*/

void Intake::bottomLimit()
{
	this->intakeMotor.output(0);
	//this->intakeEncoder.reset();
	currentMotorOutput = 0;
}

void Intake::topLimit()
{
	this->intakeMotor.output(0);
	currentMotorOutput = 0;
}

void Intake::reset()
{
	//Reset the encoders and the height of the rack and pinion!
	intakeMotor.output(resetSpeed);
	
	//This will cause the rack and pinion to drop and the interrupts above should make the motor not die
}

float Intake::coerce(float value, float high, float low)
{
	value = value > high ? high : value;
	value = value < low ? low : value;
	return value;
}

String Intake::getStateString()
{
	return this->state;
}

void Intake::resetRack()
{
	while(this->lowLimitSwitch.read() != HIGH) // This MUST bottom out!
	{
		//Output <0 to go down
		this->intakeMotor.output(currentMotorOutput);
	}
}

int Intake::getIntakeReturn()
{
	return this->intakeReturn;
}