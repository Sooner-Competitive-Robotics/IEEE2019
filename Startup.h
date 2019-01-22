#ifndef STARTUP_H
#define STARTUP_H

StepperMotorDrivetrain drivetrain;
//SteeperHalfDrivetrain drivetrain;

void robotSetup() {
	drivetrain.initFrontLeft(FRONT_LEFT_MOT_PIN1, FRONT_LEFT_MOT_PIN2, FRONT_LEFT_MOT_PIN3, FRONT_LEFT_MOT_PIN4);
	drivetrain.initBackLeft(BACK_LEFT_MOT_PIN1, BACK_LEFT_MOT_PIN2, BACK_LEFT_MOT_PIN3, BACK_LEFT_MOT_PIN4);
	drivetrain.initFrontRight(FRONT_RIGHT_MOT_PIN1, FRONT_RIGHT_MOT_PIN2, FRONT_RIGHT_MOT_PIN3, FRONT_RIGHT_MOT_PIN4);
	drivetrain.initBackRight(BACK_RIGHT_MOT_PIN1, BACK_RIGHT_MOT_PIN2, BACK_RIGHT_MOT_PIN3, BACK_RIGHT_MOT_PIN4);
	drivetrain.setRPM(25);
}

#endif