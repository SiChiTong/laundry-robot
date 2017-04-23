#include "robot/robot.h"
#include "utils/utils.h"

float Robot::getThetaDesiredNavigation() {
  return waypointSet.getThetaDesired(x, y);
}
