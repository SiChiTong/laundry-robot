#include "robot/robot.h"
#include "utils/utils.h"

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
    thetaDesired = waypointSet.getThetaDesired(x, y);
    velocity = transformVelocity(theta, thetaDesired);
    omega = transformOmega(theta, thetaDesired);

    targetVelocityLeft = (2*velocity + omega*wheelAxelLength)/(2*wheelRadius);
    targetVelocityRight = (2*velocity - omega*wheelAxelLength)/(2*wheelRadius);
  }
}
