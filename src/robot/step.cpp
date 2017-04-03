#include "robot/robot.h"

void Robot::step() {
  readSensors();
  waypointSet.step(x, y);

  stepNavigation();
//  stepObstacleBoundaryFollow();
//  stepObstacleAvoidance();
//  stepBumpers();
  stepRemote();
  stepMotors();

  updateOdometry();
  updateThetaDesired();

  delay(50);
}
