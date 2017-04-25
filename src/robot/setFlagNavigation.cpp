#include "robot/robot.h"
#include "utils/utils.h"

void Robot::setFlagNavigation() {
  bool isComplete = waypointSet.isComplete(x, y);
  if (isComplete == true) {
    requestFlagChange(FLAG_SYSTEM_COMPLETE);
  } else {
    requestFlagChange(FLAG_NAVIGATION);
  }
}
