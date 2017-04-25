#include "robot/robot.h"
#include "utils/utils.h"

void Robot::setFlagObstacleAvoidance() {
  bool flagObstacleAvoidance = (flag == FLAG_AVOID_OBSTACLE);
  bool lastFlagObstacleAvoidance = flagObstacleAvoidance;

  int distanceThresholdEnter = 6;
  int distanceThresholdExit = 12;

  float distanceLeftLeft = sensorLeftLeft.getPreviousRead();
  float distanceLeft = sensorLeft.getPreviousRead();
  float distanceForward = sensorForward.getPreviousRead();
  float distanceRight = sensorRight.getPreviousRead();
  float distanceRightRight = sensorRightRight.getPreviousRead();

  float distanceLeast = distanceLeftLeft;
  if (distanceLeast > distanceLeft) distanceLeast = distanceLeft;
  if (distanceLeast > distanceForward) distanceLeast = distanceForward;
  if (distanceLeast > distanceRight) distanceLeast = distanceRight;
  if (distanceLeast > distanceRightRight) distanceLeast = distanceRightRight;

  if (flagObstacleAvoidance == false) {
    flagObstacleAvoidance = distanceLeast <= distanceThresholdEnter;
  } else {
    flagObstacleAvoidance = distanceLeast < distanceThresholdExit;
  }

  // set flag or release flag
  if (flagObstacleAvoidance == true) {
    requestFlagChange(FLAG_AVOID_OBSTACLE);
  } else if (lastFlagObstacleAvoidance == true && flag == FLAG_AVOID_OBSTACLE) {
    resetFlag();
  }
}
