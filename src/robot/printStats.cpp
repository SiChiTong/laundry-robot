#include "robot/robot.h"
#include "robot/getThetaDesiredAvoidObstacle.h"

void Robot::printStats() {
  // Serial.print("Position: ");
  // Serial.print(x);
  // Serial.print(", ");
  // Serial.print(y);
  // Serial.print(", ");
  // Serial.println(theta);

  float distanceLeftLeft = sensorLeftLeft.getPreviousRead();
  float distanceLeft = sensorLeft.getPreviousRead();
  float distanceForward = sensorForward.getPreviousRead();
  float distanceRight = sensorRight.getPreviousRead();
  float distanceRightRight = sensorRightRight.getPreviousRead();

  float thetaDesired = getThetaDesiredAvoidObstacle(0, 18, \
    sensorLeftLeft, sensorLeft, sensorForward, sensorRight, sensorRightRight);

  Serial.print(thetaDesired);
  Serial.print(": ");
  Serial.print(distanceLeftLeft);
  Serial.print(", ");
  Serial.print(distanceLeft);
  Serial.print(", ");
  Serial.print(distanceForward);
  Serial.print(", ");
  Serial.print(distanceRight);
  Serial.print(", ");
  Serial.println(distanceRightRight);
}
