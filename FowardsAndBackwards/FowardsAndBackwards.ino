#include <RobotLib.h>
#include <IEEErobot2019.h>

bool turnDone = false;

void setup()
{
  //Initialize motors and basic drivetrain functions
  drivetrain.initLeft(LEFT_IN_1, LEFT_IN_2, LEFT_IN_3, LEFT_IN_4);
  drivetrain.initRight(RIGHT_IN_1, RIGHT_IN_2, RIGHT_IN_3, RIGHT_IN_4);
  drivetrain.setRPM(DRIVE_RPM);
}

void loop()
{
  drivetrain.setRPM(DRIVE_RPM);
  drivetrain.step(drivetrain.convertInchesToSteps(12), drivetrain.convertInchesToSteps(12));
  commandTransition();

  drivetrain.setRPM(DRIVE_RPM);
  drivetrain.step(drivetrain.convertInchesToSteps(-12), drivetrain.convertInchesToSteps(-12));
  commandTransition();

  while(true){};
}

