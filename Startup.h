#ifndef STARTUP_H
#define STARTUP_H

//StepperMotorDrivetrain drivetrain;
SteeperHalfDrivetrain drivetrain;

void robotSetup() {
	drivetrain.initFront(FRONT_LEFT_MOT_PIN1, FRONT_LEFT_MOT_PIN2, FRONT_LEFT_MOT_PIN3, FRONT_LEFT_MOT_PIN4);
	drivetrain.initBack(FRONT_RIGHT_MOT_PIN1, FRONT_RIGHT_MOT_PIN2, FRONT_RIGHT_MOT_PIN3, FRONT_RIGHT_MOT_PIN4);
	drivetrain.setRPM(25);
}

#endif