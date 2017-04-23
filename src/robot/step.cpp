#include "robot/robot.h"

void Robot::step() {
  readSensors();
  waypointSet.step(x, y);

  // default behavior: do nothing
  targetVelocityLeft = 0;
  targetVelocityRight = 0;

  // set flags
  setFlagObstacleBoundaryFollow();
  setFlagObstacleAvoidance();

  // targetVelocityLeft = velocitySlow;
  // targetVelocityRight = velocitySlow;

  // step subsystems
  if (navigationComplete == false) {
    stepNavigation();
    stepObstacleBoundaryFollow();
    // stepObstacleAvoidance();
    // stepBumpers();
  }

  // stepLaundryTask();
  stepRemote();
  stepMotors();

  updateOdometry();
  updateThetaDesired();

  delay(50);
}
