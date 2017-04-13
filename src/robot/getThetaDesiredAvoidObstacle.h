#include "robot/robot.h"

float getThetaDesiredAvoidObstacle(float _robotTheta, float enterDistance, SensorUltrasonic sensorLeft, SensorUltrasonic sensorForward, SensorUltrasonic sensorRight) {
  float robotTheta = _robotTheta;
  if (robotTheta < 0) {
    robotTheta += TWO_PI;
  }

  int distanceLeft = sensorLeft.getPreviousRead();
  int distanceForward = sensorForward.getPreviousRead();
  int distanceRight = sensorRight.getPreviousRead();

  // max sensor distance to keep readings relevant to weighting
  if (distanceLeft > enterDistance) distanceLeft = enterDistance;
  if (distanceForward > enterDistance) distanceForward = enterDistance;
  if (distanceRight > enterDistance) distanceRight = enterDistance;

  // avoidance vectors for each sensor
  // desired theta is relative, so must add robot's theta
  float thetaLeft = robotTheta + sensorLeft.theta + PI;
  float thetaForward = robotTheta + sensorForward.theta + PI;
  float thetaRight = robotTheta + sensorRight.theta + PI;

  // vote towards sensor theta if no object detected
  if (distanceLeft > enterDistance) thetaLeft -= PI;
  if (distanceForward > enterDistance) thetaForward -= PI;
  if (distanceRight > enterDistance) thetaRight -= PI;

  // make sure distance > 0, default value of 1
  float distanceInverseLeft = 1;
  float distanceInverseForward = 1;
  float distanceInverseRight = 1;
  if (distanceLeft > 0) distanceInverseLeft = 1.0 / distanceLeft;
  if (distanceForward > 0) distanceInverseForward = 1.0 / distanceForward;
  if (distanceRight > 0) distanceInverseRight = 1.0 / distanceRight;
  float distanceInverseSum = distanceInverseLeft + distanceInverseForward + distanceInverseRight; //0.188319

  float weightLeft = distanceInverseLeft / distanceInverseSum;
  float weightForward = distanceInverseForward / distanceInverseSum;
  float weightRight = distanceInverseRight / distanceInverseSum;

  float yHatLeft = thetaLeft * weightLeft;
  float yHatForward = thetaForward * weightForward;
  float yHatRight = thetaRight * weightRight;

  return yHatLeft + yHatForward + yHatRight;
}
