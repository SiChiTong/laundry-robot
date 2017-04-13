#include "robot/robot.h"
#include "utils/utils.h"
#include "robot/getThetaDesiredAvoidObstacle.h"

float thetaDesired = 0;
int countObstacleAvoidance = 0;
bool lastFlagObstacleAvoidance = false;
void Robot::stepObstacleAvoidance() {
  float distanceThresholdDanger = 6;
  float distanceThresholdEnter = 12;
  float distanceThresholdExit = 18;

  float distanceLeft = sensorLeft.getPreviousRead();
  float distanceForward = sensorForward.getPreviousRead();
  float distanceRight = sensorRight.getPreviousRead();

  float distanceLeast = distanceLeft;
  if (distanceLeast > distanceForward) distanceLeast = distanceForward;
  if (distanceLeast > distanceRight) distanceLeast = distanceRight;

  if (flagObstacleAvoidance == true && lastFlagObstacleAvoidance == false) {
    // begin obstacle avoidance subsystem
    countObstacleAvoidance = 0;
    thetaDesired = getThetaDesiredAvoidObstacle(theta, distanceThresholdEnter, \
      sensorLeft, sensorForward, sensorRight);
    thetaDesired = constrainAngle(thetaDesired);

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
    float velocity = velocitySlow;

    thetaDesired = getThetaDesiredAvoidObstacle(theta, distanceThresholdEnter, \
      sensorLeft, sensorForward, sensorRight);
    thetaDesired = constrainAngle(thetaDesired);
    Serial.println(thetaDesired - theta);

    float omega = regulatorObstacleAvoidanceOmega.Compute(theta, thetaDesired);

    if (distanceLeast <= distanceThresholdEnter) {
      float factor = (distanceLeast - distanceThresholdDanger) / (distanceThresholdEnter - distanceThresholdDanger);
      if (factor < 1) factor = -1;
      else if (factor > 1) factor = 1;
      velocity *= factor;
    }

    targetVelocityLeft = (2*velocity + omega*wheelAxelLength)/(2*wheelRadius);
    targetVelocityRight = (2*velocity - omega*wheelAxelLength)/(2*wheelRadius);
  } else {
    regulatorObstacleAvoidanceOmega.Compute(0, 0);
  }

  lastFlagObstacleAvoidance = flagObstacleAvoidance;
}
