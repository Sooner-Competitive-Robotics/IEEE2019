#ifndef CLAW_H
#define CLAW_H

#include <Servo.h>
#include <Arduino.h>

class Claw
{
	public:
		Claw();
		
		void begin(Servo wrist, Servo fist);
		
		void open();
		
		void grab();
		
	private:
		Servo wristServo;

		Servo fistServo;
		