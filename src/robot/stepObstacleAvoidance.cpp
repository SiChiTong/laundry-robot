#include "robot/robot.h"
#include "utils/utils.h"

bool lastFlagObstacleAvoidance = false;
void Robot::stepObstacleAvoidance() {
  if (flagObstacleAvoidance == true && lastFlagObstacleAvoidance == false) {
    Serial.println("Obstacle avoidance system begin");
  } else if (flagObstacleAvoidance == false && lastFlagObstacleAvoidance == true) {
    Serial.println("Obstacle avoidance system end");
  }

  if (flagObstacleAvoidance == true) {
    thetaDesired = getThetaDesiredAvoidObstacle(12);
    velocity = transformVelocity(theta, thetaDesired);
    omega = transformOmega(theta, thetaDesired);

    targetVelocityLeft = (2*velocity + omega*wheelAxelLength)/(2*wheelRadius);
    targetVelocityRight = (2*velocity - omega*wheelAxelLength)/(2*wheelRadius);
  }

  lastFlagObstacleAvoidance = flagObstacleAvoidance;
}
