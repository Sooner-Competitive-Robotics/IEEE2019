#include <RobotLib.h>
#include <IEEErobot2018.h>

bool turnDone = false;

void setup()
{
  robotSetup();
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

