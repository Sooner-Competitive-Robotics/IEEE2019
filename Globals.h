#ifndef GLOBALS_H
#define GLOBALS_H

// 191 steps / foot (forwards and backwards)

#define FRONT_LEFT_MOT_PIN1 10//2
#define FRONT_LEFT_MOT_PIN2 11//3
#define FRONT_LEFT_MOT_PIN3 12//4
#define FRONT_LEFT_MOT_PIN4 13//5

#define BACK_LEFT_MOT_PIN1 5//6
#define BACK_LEFT_MOT_PIN2 4//7
#define BACK_LEFT_MOT_PIN3 3//8
#define BACK_LEFT_MOT_PIN4 2//9

#define FRONT_RIGHT_MOT_PIN1 A0//10
#define FRONT_RIGHT_MOT_PIN2 A1//11
#define FRONT_RIGHT_MOT_PIN3 A2//12
#define FRONT_RIGHT_MOT_PIN4 A3//13

#define BACK_RIGHT_MOT_PIN1 6//A0
#define BACK_RIGHT_MOT_PIN2 7//A1
#define BACK_RIGHT_MOT_PIN3 8//A2
#define BACK_RIGHT_MOT_PIN4 9//A3

#define GYRO_THRESHOLD 1.5

float GYRO_PITCH;
float GYRO_ROLL;
float GYRO_YAW;

#define ARM_MOT_PIN1 6
#define ARM_MOT_PIN2 7

#define WRIST_PIN1 4

#define FIST_PIN1 5

#define LOW_SWITCH 9
#define HIGH_SWITCH 8

#endif