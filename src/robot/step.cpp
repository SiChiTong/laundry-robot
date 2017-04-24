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

  // step subsystems
  if (navigationComplete == false) {
    stepNavigation();
    stepObstacleBoundaryFollow();
    stepObstacleAvoidance();
    // stepBumpers();
  }

  // stepLaundryTask();
  stepRemote();
  stepMotors();

  updateOdometry();

  delay(50);
}
