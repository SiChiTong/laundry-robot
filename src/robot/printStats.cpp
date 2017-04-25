#include "robot/robot.h"

void Robot::printStats() {
  Serial.print(flag);
  Serial.print(", ");
  Serial.print(x);
  Serial.print("x, ");
  Serial.print(y);
  Serial.print("y, ");
  Serial.print(theta);
  Serial.print("t, ");
  Serial.print(thetaDesired);
  Serial.print("td, ");
  Serial.print(velocity);
  Serial.print("v, ");
  Serial.print(omega);
  Serial.print("o, ");
  Serial.print(targetVelocityLeft);
  Serial.print("tvl, ");
  Serial.print(targetVelocityRight);
  Serial.print("tvr, ");
  Serial.print(regulatorMotorLeft.GetPreviousValue());
  Serial.print("pl, ");
  Serial.print(regulatorMotorRight.GetPreviousValue());
  Serial.print("pr, ");
  Serial.print(sensorLeftLeft.getPreviousRead());
  Serial.print("s1, ");
  Serial.print(sensorLeft.getPreviousRead());
  Serial.print("s2, ");
  Serial.print(sensorForward.getPreviousRead());
  Serial.print("s3, ");
  Serial.print(sensorRight.getPreviousRead());
  Serial.print("s4, ");
  Serial.print(sensorRightRight.getPreviousRead());
  Serial.println("s5");
}
