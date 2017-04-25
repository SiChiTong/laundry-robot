#include "robot/robot.h"
#include "utils/utils.h"

float distanceStart = 0;
void Robot::setFlagObstacleBoundaryFollow() {
  bool flagBoundaryFollow = (flag == FLAG_FOLLOW_BOUNDARY);
  bool lastFlagBoundaryFollow = flagBoundaryFollow;

  float thetaNavigation = getThetaDesiredNavigation();
  float thetaAvoidObstacle = getThetaDesiredAvoidObstacle(8);
  float delta = abs(thetaNavigation - thetaAvoidObstacle);

  if (flagBoundaryFollow == false) {
    flagBoundaryFollow = delta > PI / 2;
    if (flagBoundaryFollow == true) {
      distanceStart = waypointSet.getErrorDistance(x, y);
    }
  } else {
    float distance = waypointSet.getErrorDistance(x, y);
    bool isCloser = (distance + 6.0 < distanceStart);
    bool isClear = (delta > PI / 2);
    flagBoundaryFollow = !(isCloser && isClear);
  }

  // turn off if no obstacle detected
  if (!isObstacleDetected(12)) {
    flagBoundaryFollow = false;
  }

  // set flag or release flag
  if (flagBoundaryFollow == true) {
    requestFlagChange(FLAG_FOLLOW_BOUNDARY);
  } else if (lastFlagBoundaryFollow == true && flag == FLAG_FOLLOW_BOUNDARY) {
    resetFlag();
  }
}
