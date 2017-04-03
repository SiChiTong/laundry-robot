#include "robot/robot.h"

void Robot::readSensors() {
  sensorForward.readDistanceInches();
  sensorLeft.readDistanceInches();
  sensorRight.readDistanceInches();
}
