#include "robot/robot.h"

void Robot::printStats() {
  Serial.print(x);
  Serial.print("x, ");
  Serial.print(y);
  Serial.print("y, ");
  Serial.print(theta);
  Serial.print("t, ");
  Serial.print(sensorLeftLeft.getPreviousRead());
  Serial.print("s1, ");
  Serial.print(sensorLeft.getPreviousRead());
  Serial.print("s2, ");
  Serial.print(sensorForward.getPreviousRead());
  Serial.print("s3, ");
  Serial.print(sensorRight.getPreviousRead());
  Serial.print("s4, ");
  Serial.print(sensorRightRight.getPreviousRead());
  Serial.print("s5, ");
  Serial.print(regulatorMotorLeft.GetPreviousValue());
  Serial.print("pl, ");
  Serial.print(regulatorMotorRight.GetPreviousValue());
  Serial.print("pr, ");
  Serial.print(regulatorNavigationOmega.GetPreviousValue());
  Serial.print("pn, ");
  Serial.print(regulatorObstacleBoundaryFollowOmega.GetPreviousValue());
  Serial.print("pfw, ");
  Serial.print(regulatorObstacleAvoidanceOmega.GetPreviousValue());
  Serial.println("pao");
}
