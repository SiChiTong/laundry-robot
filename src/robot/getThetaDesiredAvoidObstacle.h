#include "robot/robot.h"
#include "utils/utils.h"

static float getThetaDesiredAvoidObstacle(float _robotTheta, float enterDistance, SensorUltrasonic sensorLeftLeft, SensorUltrasonic sensorLeft, SensorUltrasonic sensorForward, SensorUltrasonic sensorRight, SensorUltrasonic sensorRightRight) {
  float robotTheta = _robotTheta;
  if (robotTheta < 0) {
    robotTheta += TWO_PI;
  }

  // create vectors {{ magnitude, direction }}
  int sensorCount = 5;
  float vectors[sensorCount][2] = {{0,0},{0,0},{0,0},{0,0},{0,0}};
  vectors[0][0] = sensorLeftLeft.getPreviousRead();
  vectors[0][1] = robotTheta + sensorLeftLeft.theta + PI;
  vectors[1][0] = sensorLeft.getPreviousRead();
  vectors[1][1] = robotTheta + sensorLeft.theta + PI;
  vectors[2][0] = sensorForward.getPreviousRead();
  vectors[2][1] = robotTheta + sensorForward.theta + PI;
  vectors[3][0] = sensorRight.getPreviousRead();
  vectors[3][1] = robotTheta + sensorRight.theta + PI;
  vectors[4][0] = sensorRightRight.getPreviousRead();
  vectors[4][1] = robotTheta + sensorRightRight.theta + PI;

  float xSum = 0;
  float ySum = 0;

  for (int i = 0; i < sensorCount; i++) {
    // max out distance and rotate vector by PI
    // if no object is within range
    if (vectors[i][0] > enterDistance) {
      vectors[i][0] = enterDistance;
      vectors[i][1] -= PI;
    }

    // set magnitude as inverse
    vectors[i][0] = 1.0 / vectors[i][0];

    // compute x y coordinates for vectors
    xSum += vectors[i][0] * cos(vectors[i][1]);
    ySum += vectors[i][0] * sin(vectors[i][1]);
  }

  return atan2(ySum, xSum);
}
