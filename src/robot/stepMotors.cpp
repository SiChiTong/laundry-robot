#include "robot/robot.h"

void Robot::stepMotors() {
  if (autonomousMode == true) {
    if (targetVelocityLeft == 0) {
      motorLeft.stop();
    } else {
      float motorPwmLeft = regulatorMotorLeft.Compute(velocityLeft, targetVelocityLeft);
      motorLeft.step(motorPwmLeft);
    }

    if (targetVelocityRight == 0) {
      motorRight.stop();
    } else {
      float motorPwmRight = regulatorMotorRight.Compute(velocityRight, targetVelocityRight);
      motorRight.step(motorPwmRight);
    }
  }
}
