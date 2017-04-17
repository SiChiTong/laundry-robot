#include "robot/robot.h"
#include "utils/utils.h"

static float getThetaDesiredAvoidObstacle(float _robotTheta, float enterDistance, SensorUltrasonic sensorLeftLeft, SensorUltrasonic sensorLeft, SensorUltrasonic sensorForward, SensorUltrasonic sensorRight, SensorUltrasonic sensorRightRight) {
  float robotTheta = _robotTheta;
  if (robotTheta < 0) {
    robotTheta += TWO_PI;
  }

  float distanceLeftLeft = sensorLeftLeft.getPreviousRead();
  float distanceLeft = sensorLeft.getPreviousRead();
  float distanceForward = sensorForward.getPreviousRead();
  float distanceRight = sensorRight.getPreviousRead();
  float distanceRightRight = sensorRightRight.getPreviousRead();

  // avoidance vectors for each sensor
  // desired theta is relative, so must add robot's theta
  float thetaLeftLeft = robotTheta + sensorLeftLeft.theta + PI;
  float thetaLeft = robotTheta + sensorLeft.theta + PI;
  float thetaForward = robotTheta + sensorForward.theta + PI;
  float thetaRight = robotTheta + sensorRight.theta + PI;
  float thetaRightRight = robotTheta + sensorRightRight.theta + PI;

  // vote towards sensor theta if no object detected
  // max sensor distance to keep readings relevant to weighting
  if (distanceLeftLeft > enterDistance) {
    thetaLeftLeft += PI;
    distanceLeftLeft = enterDistance;
  }

  if (distanceLeft > enterDistance) {
    thetaLeft += PI;
    distanceLeft = enterDistance;
  }

  if (distanceForward > enterDistance) {
    thetaForward -= PI;
    distanceForward = enterDistance;
  }

  if (distanceRight > enterDistance) {
    thetaRight -= PI;
    distanceRight = enterDistance;
  }

  if (distanceRightRight > enterDistance) {
    thetaRightRight -= PI;
    distanceRightRight = enterDistance;
  }

  // make sure distance > 0, default value of 1
  float distanceInverseLeftLeft = 1;
  float distanceInverseLeft = 1;
  float distanceInverseForward = 1;
  float distanceInverseRight = 1;
  float distanceInverseRightRight = 1;
  if (distanceLeftLeft > 0) distanceInverseLeftLeft = 1.0 / distanceLeftLeft;
  if (distanceLeft > 0) distanceInverseLeft = 1.0 / distanceLeft;
  if (distanceForward > 0) distanceInverseForward = 1.0 / distanceForward;
  if (distanceRight > 0) distanceInverseRight = 1.0 / distanceRight;
  if (distanceRightRight > 0) distanceInverseRightRight = 1.0 / distanceRightRight;
  float distanceInverseSum = distanceInverseLeftLeft + distanceInverseLeft + \
    distanceInverseForward + distanceInverseRight + distanceInverseRightRight;

  float weightLeftLeft = distanceInverseLeftLeft / distanceInverseSum;
  float weightLeft = distanceInverseLeft / distanceInverseSum;
  float weightForward = distanceInverseForward / distanceInverseSum;
  float weightRight = distanceInverseRight / distanceInverseSum;
  float weightRightRight = distanceInverseRightRight / distanceInverseSum;

  float yHatLeftLeft = thetaLeftLeft * weightLeftLeft;
  float yHatLeft = thetaLeft * weightLeft;
  float yHatForward = thetaForward * weightForward;
  float yHatRight = thetaRight * weightRight;
  float yHatRightRight = thetaRightRight * weightRightRight;

  float thetaDesired = yHatLeftLeft + yHatLeft + yHatForward + yHatRight + yHatRightRight;
  thetaDesired = constrainAngle(thetaDesired);
  return thetaDesired;
}
