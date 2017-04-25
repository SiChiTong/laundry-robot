#include "robot/robot.h"
#include "utils/utils.h"

void Robot::resetFlag() {
  flag = FLAG_RESET;
  Serial.println("Control system flag reset");
}
