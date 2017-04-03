#include "robot/robot.h"

void Robot::printStats() {
  Serial.print("Position: ");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.println(theta);
}
