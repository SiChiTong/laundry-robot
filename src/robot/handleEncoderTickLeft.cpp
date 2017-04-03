#include "globals.cpp"
#include "robot/robot.h"

static void Robot::handleEncoderTickLeft() {
  if (robot.motorLeft.isMovingForward == true) {
    robot.motorLeft.incrementEncoderTickCount();
  } else if (robot.motorLeft.isMovingBackward == true) {
    robot.motorLeft.decrementEncoderTickCount();
  } else {
     robot.motorLeft.incrementEncoderTickCount();
  }
}
