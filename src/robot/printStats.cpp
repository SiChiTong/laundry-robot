#include "robot/robot.h"

void Robot::printStats() {
  Serial.print("Position: ");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.print(theta);
  Serial.print(";  ");
  Serial.print("Omega: ");
  Serial.print(omega);
  Serial.print(";  ");
  Serial.print("Desired Theta: ");
  Serial.println(thetaDesired);
//  Serial.print("Target Distance: ");
//  Serial.println(targetDistance);
//  Serial.print("Target Velocity Left: ");
//  Serial.print(targetVelocityLeft);
//  Serial.print(", Target Velocity Right: ");
//  Serial.println(targetVelocityRight);
//  Serial.print("Left PWM: ");
//  Serial.print(motorPwmLeft);
//  Serial.print(", Right PWM: ");
//  Serial.println(motorPwmRight);
//  Serial.print("Sensor Forward: ");
//  Serial.print(distanceForward);
//  Serial.print(", Sensor Left: ");
//  Serial.print(distanceLeft);
//  Serial.print(", Sensor Right: ");
//  Serial.println(distanceRight);
}
