#include "robot/robot.h"

void Robot::stepNavigation() {
  bool done = waypointSet.isComplete();
  if (done == true) {
    targetVelocityLeft = 0;
    targetVelocityRight = 0;
  } else {
    regulatorNavigationOmega.Compute();

    float velocity = velocitySlow;
    float _omega = omega;
    float errorTheta = thetaDesired - theta;
    float errorDistance = waypointSet.getErrorDistance(x, y);

    if (abs(errorTheta) > PI) {
      velocity = 0;
      _omega /= 2;
    } else if (abs(errorTheta) > PI / 2) {
      velocity /= 2;
      _omega /= 2;
    } else if (errorDistance < 24) {
      velocity /= 2;
    }

    targetVelocityLeft = (2*velocity + _omega*wheelAxelLength)/(2*wheelRadius);
    targetVelocityRight = (2*velocity - _omega*wheelAxelLength)/(2*wheelRadius);
  }
}
