#include "robot/robot.h"

void Robot::stepMotors() {
  if (flag != FLAG_REMOTE) {
    if (targetVelocityLeft == 0) {
      motorLeft.stop();
    } else {
      float motorPwmLeft = regulatorMotorLeft.Compute(velocityLeft, targetVelocityLeft);
      motorLeft.step(motorPwmLeft * 10.0);
    }

    if (targetVelocityRight == 0) {
      motorRight.stop();
    } else {
      float motorPwmRight = regulatorMotorRight.Compute(velocityRight, targetVelocityRight);
      motorRight.step(motorPwmRight * 10.0);
    }
  }
}
