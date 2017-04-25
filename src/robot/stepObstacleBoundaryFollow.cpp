#include "robot/robot.h"
#include "utils/utils.h"
#include "globals.h"

void Robot::stepObstacleBoundaryFollow() {
  if (flag == FLAG_FOLLOW_BOUNDARY) {
    float thetaDesiredNavigation = waypointSet.getThetaDesired(x, y);
    bool followRightWall = (thetaDesiredNavigation < 0);

    thetaDesired = getThetaDesiredObstacleBoundaryFollow(followRightWall);
    velocity = transformVelocity(theta, thetaDesired);
    omega = transformOmega(theta, thetaDesired);
    setTargetVelocitiesWheels(velocity, omega);
  }
}
