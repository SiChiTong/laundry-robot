#include "robot/robot.h"
#include "utils/utils.h"

void Robot::stepObstacleAvoidance() {
  if (flag == FLAG_AVOID_OBSTACLE) {
    thetaDesired = getThetaDesiredAvoidObstacle(12);
    velocity = transformVelocity(theta, thetaDesired);
    omega = transformOmega(theta, thetaDesired);
    setTargetVelocitiesWheels();
  }
}
