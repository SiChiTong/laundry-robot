#include "robot/robot.h"
#include "utils/utils.h"

float distanceStart = 0;
void Robot::setFlagObstacleBoundaryFollow() {
  float thetaNavigation = getThetaDesiredNavigation();
  float thetaAvoidObstacle = getThetaDesiredAvoidObstacle(18);
  float delta = abs(thetaNavigation - thetaAvoidObstacle);

  if (flagObstacleBoundaryFollow == false) {
    flagObstacleBoundaryFollow = delta > PI / 2;
    if (flagObstacleBoundaryFollow == true) {
      distanceStart = waypointSet.getErrorDistance(x, y);
    }
  } else {
    float distance = waypointSet.getErrorDistance(x, y);
    bool isCloser = (distance + 12 < distanceStart);
    bool isClear = (delta > PI / 2);
    flagObstacleBoundaryFollow = !(isCloser && isClear);
  }
}
