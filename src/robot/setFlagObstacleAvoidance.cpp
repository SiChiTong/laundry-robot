#include "robot/robot.h"
#include "utils/utils.h"

void Robot::setFlagObstacleAvoidance() {
  int distanceThresholdEnter = 12;
  int distanceThresholdExit = 18;

  int distanceLeft = sensorLeft.getPreviousRead();
  int distanceForward = sensorForward.getPreviousRead();
  int distanceRight = sensorRight.getPreviousRead();

  int distanceLeast = distanceLeft;
  if (distanceLeast > distanceForward) distanceLeast = distanceForward;
  if (distanceLeast > distanceRight) distanceLeast = distanceRight;

  if (flagObstacleAvoidance == false) {
    flagObstacleAvoidance = distanceLeast < distanceThresholdEnter;
  } else {
    flagObstacleAvoidance = distanceLeast < distanceThresholdExit;
  }
}
