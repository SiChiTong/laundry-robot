/*
  1. Estimate section of obstacle using sensors
  2. Compute vectors tangential to obstacle and perpendicular to obstacle
  3. Combine two vectors and steer in director of new vector
*/

#include "robot/robot.h"
#include "utils/utils.h"
#include "globals.h"

float thetaDesiredObstacleBoundaryFollow = 0;
bool lastflagObstacleBoundaryFollow = false;
bool turnLeftBoundaryFollow = false;

void obstacleBoundaryFollowBegin () {
  float x = robot.getX();
  float y = robot.getY();
  WaypointSet waypointSet = robot.getWaypointSet();
  float thetaDesiredNavigation = waypointSet.getThetaDesired(x, y);
  turnLeftBoundaryFollow = (thetaDesiredNavigation < 0);
}

void obstacleBoundaryFollowEnd () {
  Serial.println("Obstacle boundary follow system end");
  thetaDesiredObstacleBoundaryFollow = 0;
}

void Robot::stepObstacleBoundaryFollow() {
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

  if (flagObstacleBoundaryFollow == true && lastflagObstacleBoundaryFollow == false) {
    obstacleBoundaryFollowBegin();
    thetaDesiredObstacleBoundaryFollow = getThetaDesiredObstacleBoundaryFollow(turnLeftBoundaryFollow);
    Serial.print("Obstacle boundary follow system begin: ");
    Serial.println(thetaDesiredObstacleBoundaryFollow);
  } else if (flagObstacleBoundaryFollow == false && lastflagObstacleBoundaryFollow == true) {
    obstacleBoundaryFollowEnd();
  }

  if (flagObstacleBoundaryFollow == true) {
    thetaDesiredObstacleBoundaryFollow = getThetaDesiredObstacleBoundaryFollow(turnLeftBoundaryFollow);

    float velocity = velocitySlow;
    float omega = regulatorObstacleBoundaryFollowOmega.Compute(theta, thetaDesiredObstacleBoundaryFollow);

    if (distanceLeast <= distanceThresholdEnter) {
      float distanceLeastForward = distanceLeft;
      if (distanceLeastForward > distanceForward) distanceLeastForward = distanceForward;
      if (distanceLeastForward > distanceRight) distanceLeastForward = distanceRight;
      // set velocity close to zero as approach danger, negative if below danger
      // velocity *= (distanceLeastForward - distanceThresholdDanger) / (distanceThresholdEnter - distanceThresholdDanger);
      // if (distanceLeastForward - distanceThresholdDanger < 0) velocity *= 3;
      if (distanceLeastForward - distanceThresholdDanger < 0) velocity *= -1;
    }

    targetVelocityLeft = (2*velocity + omega*wheelAxelLength)/(2*wheelRadius);
    targetVelocityRight = (2*velocity - omega*wheelAxelLength)/(2*wheelRadius);
  } else {
    regulatorObstacleBoundaryFollowOmega.Compute(0, 0);
  }

  lastflagObstacleBoundaryFollow = flagObstacleBoundaryFollow;
}
