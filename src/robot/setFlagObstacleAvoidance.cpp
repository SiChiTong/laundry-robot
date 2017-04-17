#include "robot/robot.h"
#include "utils/utils.h"

void Robot::setFlagObstacleAvoidance() {
  int distanceThresholdDanger = 12;
  int distanceThresholdEnter = 18;
  int distanceThresholdExit = 24;

  float distanceLeftLeft = sensorLeftLeft.getPreviousRead();
  float distanceLeft = sensorLeft.getPreviousRead();
  float distanceForward = sensorForward.getPreviousRead();
  float distanceRight = sensorRight.getPreviousRead();
  float distanceRightRight = sensorRightRight.getPreviousRead();

  int sensorId = 0;
  float distanceLeast = distanceLeftLeft;
  if (distanceLeast > distanceLeft) {
    distanceLeast = distanceLeft;
    sensorId = 1;
  }

  if (distanceLeast > distanceForward) {
    distanceLeast = distanceForward;
    sensorId = 2;
  }

  if (distanceLeast > distanceRight) {
    distanceLeast = distanceRight;
    sensorId = 3;
  }

  if (distanceLeast > distanceRightRight) {
    distanceLeast = distanceRightRight;
    sensorId = 4;
  }

  if (flagObstacleAvoidance == false) {
    flagObstacleAvoidance = distanceLeast <= distanceThresholdEnter;
  } else {
    flagObstacleAvoidance = distanceLeast < distanceThresholdExit;
  }
}
