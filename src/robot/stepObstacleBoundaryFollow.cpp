#include "robot/robot.h"

bool runWallFollowProgram = false;
int wallFollowProgramStep = 0;
int wallFollowProgramStepCount = -1;
void Robot::stepObstacleBoundaryFollow() {
  int enterDistance = 24;
  int exitDistance = 36;

  int distanceLeft = sensorLeft.getPreviousRead();
  int distanceRight = sensorRight.getPreviousRead();
  int distanceForward = sensorForward.getPreviousRead();

  if (abs(thetaDesired - theta) > PI) {
    if (distanceLeft < enterDistance) {
      runWallFollowProgram = true;
      wallFollowProgramStep = 1;
      wallFollowProgramStepCount = -1;
    } else if (distanceRight < enterDistance) {
      runWallFollowProgram = true;
      wallFollowProgramStep = 1;
      wallFollowProgramStepCount = -1;
    }
  }

  if (runWallFollowProgram == true) {
    if (wallFollowProgramStep == 1) {
      if (distanceLeft < enterDistance / 2) {
        omega = PI / 2;
        targetVelocityLeft = (2*velocitySlow + omega*wheelAxelLength)/(2*wheelRadius);
        targetVelocityRight = (2*velocitySlow - omega*wheelAxelLength)/(2*wheelRadius);
      } else if (distanceLeft >= enterDistance / 2) {
        wallFollowProgramStep = 2;
      } else if (distanceRight < enterDistance / 2) {
        omega = -PI / 2;
        targetVelocityLeft = (2*velocitySlow + omega*wheelAxelLength)/(2*wheelRadius);
        targetVelocityRight = (2*velocitySlow - omega*wheelAxelLength)/(2*wheelRadius);
      } else if (distanceRight >= enterDistance / 2) {
        wallFollowProgramStep = 2;
      }
    } else if (wallFollowProgramStep == 2) {
      wallFollowProgramStepCount++;
      targetVelocityLeft = velocitySlow;
      targetVelocityRight = velocitySlow;

      if (wallFollowProgramStepCount >= 20) {
        runWallFollowProgram = false;
        wallFollowProgramStep = 0;
        wallFollowProgramStepCount = -1;
      }
    }
  }
}
