#include "robot/robot.h"

void Robot::stepMotors() {
  if (autonomousMode == true) {
    if (targetVelocityLeft == 0) {
      motorLeft.stop();
    } else {
      regulatorMotorLeft.Compute();
      motorLeft.step(motorPwmLeft);
    }

    if (targetVelocityRight == 0) {
      motorRight.stop();
    } else {
      regulatorMotorRight.Compute();
      motorRight.step(motorPwmRight);
    }
  }
}
