#include "robot/robot.h"
#include "utils/utils.h"

float thetaDesired = 0;
int countObstacleAvoidance = 0;
bool lastFlagObstacleAvoidance = false;
bool turnLeft = false;
void Robot::stepObstacleAvoidance() {
  float distanceThresholdDanger = 12;
  float distanceThresholdEnter = 18;
  float distanceThresholdExit = 24;

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

  if (flagObstacleAvoidance == true && lastFlagObstacleAvoidance == false) {
    // begin obstacle avoidance subsystem
    countObstacleAvoidance = 0;
    thetaDesired = getThetaDesiredAvoidObstacle(distanceThresholdEnter);
    turnLeft = thetaDesired < 0;

    Serial.print("Obstacle avoidance system begin: ");
    Serial.print(thetaDesired);
    Serial.print(", ");
    Serial.println(distanceLeast);
  } else if (flagObstacleAvoidance == false && lastFlagObstacleAvoidance == true) {
    // end obstacle avoidance subsystem
    Serial.print("Obstacle avoidance system end: ");
    Serial.println(countObstacleAvoidance);
    thetaDesired = 0;
    countObstacleAvoidance = 0;
  } else {
    countObstacleAvoidance++;
  }

  if (flagObstacleAvoidance == true) {
    thetaDesired = getThetaDesiredAvoidObstacle(distanceThresholdEnter);

    // keep turning in one direction
    // if (turnLeft == false && thetaDesired < 0) thetaDesired += TWO_PI;
    // else if (turnLeft == true && thetaDesired > 0) thetaDesired -= TWO_PI;

    float velocity = velocitySlow;
    float omega = regulatorObstacleAvoidanceOmega.Compute(theta, thetaDesired);

    if (distanceLeast <= distanceThresholdEnter) {
      float distanceLeastForward = distanceLeft;
      if (distanceLeastForward > distanceForward) distanceLeastForward = distanceForward;
      if (distanceLeastForward > distanceRight) distanceLeastForward = distanceRight;
      // set velocity close to zero as approach danger, negative if below danger
      velocity *= (distanceLeastForward - distanceThresholdDanger) / (distanceThresholdEnter - distanceThresholdDanger);

      if (distanceLeastForward - distanceThresholdDanger < 0) velocity *= 3;
    }

    targetVelocityLeft = (2*velocity + omega*wheelAxelLength)/(2*wheelRadius);
    targetVelocityRight = (2*velocity - omega*wheelAxelLength)/(2*wheelRadius);
  } else {
    regulatorObstacleAvoidanceOmega.Compute(0, 0);
  }

  lastFlagObstacleAvoidance = flagObstacleAvoidance;
}
