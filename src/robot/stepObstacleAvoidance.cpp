#include "robot/robot.h"

int FORWARD_DETECT = 0;
int LEFT_DETECT = 1;
int RIGHT_DETECT = 2;
void Robot::stepObstacleAvoidance() {
  int distanceLeft = sensorLeft.getPreviousRead();
  int distanceRight = sensorRight.getPreviousRead();
  int distanceForward = sensorForward.getPreviousRead();

  // classify detections
  int detectType = -1;
  if (distanceLeft < 12) {
    detectType = LEFT_DETECT;
  } else if (distanceRight < 12) {
    detectType = RIGHT_DETECT;
  } else if (distanceForward < 12) {
    detectType = FORWARD_DETECT;
  }

  // act on detection
  if (detectType == LEFT_DETECT) {
    // half speed, right turn
    omega = PI;
    targetVelocityRight = (-omega*wheelAxelLength)/(2*wheelRadius);
    targetVelocityLeft = (omega*wheelAxelLength)/(2*wheelRadius);
  } else if (detectType == RIGHT_DETECT) {
    // half speed, left turn
    omega = -PI;
    targetVelocityRight = (-omega*wheelAxelLength)/(2*wheelRadius);
    targetVelocityLeft = (omega*wheelAxelLength)/(2*wheelRadius);
  } else if (detectType == FORWARD_DETECT) {
    // zero speed, keep turning in same direction
    targetVelocityLeft = -velocitySlow;
    targetVelocityRight = velocitySlow;
  }
}
