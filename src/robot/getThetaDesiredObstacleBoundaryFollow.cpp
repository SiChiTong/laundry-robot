#include "robot/robot.h"
#include "utils/utils.h"

float Robot::getThetaDesiredObstacleBoundaryFollow(bool turnLeft) {
  float thetaDesiredBoundaryFollow = getThetaDesiredAvoidObstacle(24);

  // rotate avoid obstacle theta by 90 degrees
  // rotate left if navigation theta is negative
  if (turnLeft == true) {
    thetaDesiredBoundaryFollow += PI / 2;
  } else {
    thetaDesiredBoundaryFollow -= PI / 2;
  }

  return constrainAngle(thetaDesiredBoundaryFollow);
}
