#include "robot/robot.h"

void Robot::readSensors() {
  sensorLeftLeft.readDistanceInches();
  sensorLeft.readDistanceInches();
  sensorForward.readDistanceInches();
  sensorRight.readDistanceInches();
  sensorRightRight.readDistanceInches();
}
