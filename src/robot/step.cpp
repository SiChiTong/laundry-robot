#include "robot/robot.h"

void Robot::step() {
  readSensors();
  waypointSet.step(x, y);

  // set flags
  setFlagObstacleAvoidance();

  targetVelocityLeft = velocitySlow;
  targetVelocityRight = velocitySlow;

  // step subsystems
  // stepNavigation();
  // stepObstacleBoundaryFollow();
  stepObstacleAvoidance();
  // stepBumpers();
  // stepLaundryTask();
  stepRemote();
  stepMotors();

  updateOdometry();
  updateThetaDesired();

  delay(50);
}
