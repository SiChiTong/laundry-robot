#include "robot/robot.h"

void Robot::updateThetaDesired() {
  // compute actual theta needed to get to goal
  float thetaDesired = waypointSet.getThetaDesired(x, y);

  // modify theta in order to turn shortest amount
  if (thetaDesired - theta > PI && abs(theta + TWO_PI - thetaDesired) < abs(thetaDesired - theta)) {
    theta += TWO_PI;
  } else if (theta - thetaDesired > PI && abs(theta + TWO_PI - thetaDesired) > abs(thetaDesired - theta)) {
    theta -= TWO_PI;
  }
}
