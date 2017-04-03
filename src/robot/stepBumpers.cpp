#include "robot/robot.h"

bool runBumperProgram = false;
int bumperProgramStep = 0;
int bumperProgramStepCount = -1;
void Robot::stepBumpers() {
  int distanceLeft = sensorLeft.getPreviousRead();
  int distanceRight = sensorRight.getPreviousRead();
  int distanceForward = sensorForward.getPreviousRead();

  if (distanceForward < 5 || distanceLeft < 5 || distanceRight < 5) {
    runBumperProgram = true;
    bumperProgramStep = 1;
    bumperProgramStepCount = -1;
  }

  if (runBumperProgram == true) {
    if (bumperProgramStep == 1) {
      targetVelocityLeft = -velocitySlow / 2;
      targetVelocityRight = -velocitySlow / 2;

      bumperProgramStepCount++;
      if (bumperProgramStepCount >= 10) {
        bumperProgramStep = 2;
        bumperProgramStepCount = -1;
      }
    } else if (bumperProgramStep == 2) {
      if (distanceRight > distanceLeft + 5) {
        float omega = PI;
        targetVelocityRight = (-omega*wheelAxelLength)/(2*wheelRadius);
        targetVelocityLeft = (omega*wheelAxelLength)/(2*wheelRadius);
      } else if (distanceLeft > distanceRight + 5) {
        float omega = -PI;
        targetVelocityRight = (-omega*wheelAxelLength)/(2*wheelRadius);
        targetVelocityLeft = (omega*wheelAxelLength)/(2*wheelRadius);
      } else {
        float omega = PI;
        targetVelocityRight = (-omega*wheelAxelLength)/(2*wheelRadius);
        targetVelocityLeft = (omega*wheelAxelLength)/(2*wheelRadius);
      }

      bumperProgramStepCount++;
      if (bumperProgramStepCount >= 20) {
        bumperProgramStep = 0;
        bumperProgramStepCount = -1;
        runBumperProgram = false;
      }
    }
  }
}
