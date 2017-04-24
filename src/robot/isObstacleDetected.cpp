#include "robot/robot.h"
#include "utils/utils.h"

bool Robot::isObstacleDetected(float distanceThreshold) {
  int sensorCount = 5;
  int distances[sensorCount] = {156, 156, 156, 156, 156};
  distances[0] = sensorLeftLeft.getPreviousRead();
  distances[1] = sensorLeft.getPreviousRead();
  distances[2] = sensorForward.getPreviousRead();
  distances[3] = sensorRight.getPreviousRead();
  distances[4] = sensorRightRight.getPreviousRead();

  int distanceLeast = 156;
  for (int i = 0; i < sensorCount; i++) {
    if (distances[i] < distanceLeast) {
      distanceLeast = distances[i];
    }
  }

  return distanceLeast < distanceThreshold;
}
