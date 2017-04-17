#include "robot/robot.h"

void Robot::stepNavigation() {
  bool done = waypointSet.isComplete(x, y);
  if (navigationComplete == true) {
    targetVelocityLeft = 0;
    targetVelocityRight = 0;
  } else if (done == true) {
    navigationComplete = true;
    Serial.println("At final waypoint. Navigation complete.");
    targetVelocityLeft = 0;
    targetVelocityRight = 0;
  } else {
    float velocity = velocitySlow;
    float thetaDesired = waypointSet.getThetaDesired(x, y);
    float errorTheta = thetaDesired - theta;
    float errorDistance = waypointSet.getErrorDistance(x, y);
    float omega = regulatorNavigationOmega.Compute(theta, thetaDesired);

    if (abs(errorTheta) > PI) {
      velocity = 0;
      omega /= 4;
    } else if (abs(errorTheta) > PI / 2) {
      velocity /= 4;
      omega /= 1;
    } else if (errorDistance < 24) {
      velocity /= 2;
    }

    targetVelocityLeft = (2*velocity + omega*wheelAxelLength)/(2*wheelRadius);
    targetVelocityRight = (2*velocity - omega*wheelAxelLength)/(2*wheelRadius);
  }
}
