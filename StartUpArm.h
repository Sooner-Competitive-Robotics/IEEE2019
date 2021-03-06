#ifndef STARTUPARM_H
#define STARTUPARM_H

#include "StepperMotorDrivetrain.h"
#include "Globals.h"
#include "StartUpDrive.h"
#include "StartUpArm.h"
#include "MPU6050.h"
#include "Arm.h"
#include <Servo.h>

Arm arm;

Servo fistServo;
Servo wristServo;
Motor rackAndPinion;

//const int MPU_addr = 0x68;  // I2C address of the MPU-6050
//int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
/*
void checkSettings()
{
	Serial.println();

	Serial.print(" * Sleep Mode:        ");
	Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");

	Serial.print(" * Clock Source:      ");
	switch(mpu.getClockSource())
	{
		case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
		case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
		case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
		case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
		case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
		case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
		case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
	}

	Serial.print(" * Gyroscope:         ");
	switch(mpu.getScale())
	{
		case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;
		case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;
		case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;
		case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;
	} 

	Serial.print(" * Gyroscope offsets: ");
	Serial.print(mpu.getGyroOffsetX());
	Serial.print(" / ");
	Serial.print(mpu.getGyroOffsetY());
	Serial.print(" / ");
	Serial.println(mpu.getGyroOffsetZ());

	Serial.println();
}

void updateGyro()
{
	Vector rawGyro = mpu.readRawGyro();
	Vector normGyro = mpu.readNormalizeGyro();

	Serial.print(" Xraw = ");
	Serial.print(rawGyro.XAxis);
	Serial.print(" Yraw = ");
	Serial.print(rawGyro.YAxis);
	Serial.print(" Zraw = ");
	Serial.println(rawGyro.ZAxis);

	Serial.print(" Xnorm = ");
	Serial.print(normGyro.XAxis);
	Serial.print(" Ynorm = ");
	Serial.print(normGyro.YAxis);
	Serial.print(" Znorm = ");
	Serial.println(normGyro.ZAxis);
	
	GYRO_PITCH = rawGyro.XAxis;
	GYRO_YAW = rawGyro.YAxis;
	GYRO_ROLL = rawGyro.ZAxis;

}
*/
void armSetup() 
{	
	DigitalDevice lowSwitch(LOW_SWITCH, INPUT);
	DigitalDevice highSwitch(HIGH_SWITCH, INPUT);

	//fistServo.attach(FIST_PIN1);
	//wristServo.attach(WRIST_PIN1);
	
	lowSwitch.pullUp();
	highSwitch.pullUp();
	
	rackAndPinion.begin(ARM_MOT_PIN1, ARM_MOT_PIN2);
	
	arm.begin(FIST_PIN1, WRIST_PIN1, rackAndPinion, lowSwitch, highSwitch);
	
	//Serial.println("Initialize MPU6050");
	//mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G);
	/*while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
	{
		Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
		delay(500);
	}*/
	
	Serial.begin(115200);

	//drivetrain.initFrontLeft(FRONT_LEFT_MOT_PIN1, FRONT_LEFT_MOT_PIN2, FRONT_LEFT_MOT_PIN3, FRONT_LEFT_MOT_PIN4);
	//drivetrain.initBackLeft(BACK_LEFT_MOT_PIN1, BACK_LEFT_MOT_PIN2, BACK_LEFT_MOT_PIN3, BACK_LEFT_MOT_PIN4);
	//drivetrain.initFrontRight(FRONT_RIGHT_MOT_PIN1, FRONT_RIGHT_MOT_PIN2, FRONT_RIGHT_MOT_PIN3, FRONT_RIGHT_MOT_PIN4);
	//drivetrain.initBackRight(BACK_RIGHT_MOT_PIN1, BACK_RIGHT_MOT_PIN2, BACK_RIGHT_MOT_PIN3, BACK_RIGHT_MOT_PIN4);
	//drivetrain.setRPM(25);
	
	//attachInterrupt(digitalPinToInterrupt(0), updateGyro, CHANGE);
	
	// Initialize MPU6050
	//Serial.println("Initialize MPU6050");
	/*while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
	{
		Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
		delay(500);
	}*/

	// If you want, you can set gyroscope offsets
	// mpu.setGyroOffsetX(155);
	// mpu.setGyroOffsetY(15);
	// mpu.setGyroOffsetZ(15);

	// Calibrate gyroscope. The calibration must be at rest.
	// If you don't want calibrate, comment this line.
	//mpu.calibrateGyro();

	// Set threshold sensivty. Default 3.
	// If you don't want use threshold, comment this line or set 0.
	//mpu.setThreshold(3);
	

	// Check settings
	//checkSettings();
	
}

/*
bool smartDrive(float targetDistance, float targetAngle)
{
	float currSteps = 0;
	//float currAngle = GYRO_PITCH; // Get angle
	
	while(currSteps < targetDistance)
	{
		if(abs(GYRO_PITCH - targetAngle) < GYRO_THRESHOLD)
		{
			if(GYRO_PITCH > targetAngle)
			{
				drivetrain.strafe(0,-1,1);
			}
			else if (GYRO_PITCH < targetAngle)
			{
				drivetrain.strafe(0,1,1);
			}
		}
		else 
		{
			if(targetDistance > 0)
			{
				drivetrain.strafe(1,0,1);
			
				currSteps++;
			}
			else if (targetDistance < 0)
			{
				drivetrain.strafe(-1,0,1);
			
				currSteps++;
			}
		}
		
	}	
	
	return true;
}
*/


#endif