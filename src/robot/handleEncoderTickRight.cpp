#include "globals.cpp"
#include "robot/robot.h"

static void Robot::handleEncoderTickRight() {
  if (robot.motorRight.isMovingForward == true) {
    robot.motorRight.incrementEncoderTickCount();
  } else if (robot.motorRight.isMovingBackward == true) {
    robot.motorRight.decrementEncoderTickCount();
  } else {
    robot.motorRight.decrementEncoderTickCount();
  }
}
