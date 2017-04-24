#include "robot/robot.h"
#include "utils/utils.h"
#include "globals.h"

bool lastflagObstacleBoundaryFollow = false;

void Robot::stepObstacleBoundaryFollow() {
  if (flagObstacleBoundaryFollow == true && lastflagObstacleBoundaryFollow == false) {
    Serial.println("Obstacle boundary follow system begin");
  } else if (flagObstacleBoundaryFollow == false && lastflagObstacleBoundaryFollow == true) {
    Serial.println("Obstacle boundary follow system end");
  }

  if (flagObstacleBoundaryFollow == true) {
    float thetaDesiredNavigation = waypointSet.getThetaDesired(x, y);
    bool followRightWall = (thetaDesiredNavigation < 0);

    thetaDesired = getThetaDesiredObstacleBoundaryFollow(followRightWall);
    velocity = transformVelocity(theta, thetaDesired);
    omega = transformOmega(theta, thetaDesired);

    targetVelocityLeft = (2*velocity + omega*wheelAxelLength)/(2*wheelRadius);
    targetVelocityRight = (2*velocity - omega*wheelAxelLength)/(2*wheelRadius);
  }

  lastflagObstacleBoundaryFollow = flagObstacleBoundaryFollow;
}
