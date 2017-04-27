#include "robot/robot.h"
#include "utils/utils.h"

void Robot::stepNavigation() {
  if (flag == FLAG_NAVIGATION) {
    thetaDesired = waypointSet.getThetaDesired(x, y);
    velocity = transformVelocity(theta, thetaDesired);
    omega = transformOmega(theta, thetaDesired);
    setTargetVelocitiesWheels();
  }
}
