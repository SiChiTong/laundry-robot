#include "robot/robot.h"

float getThetaDesired(SensorUltrasonic sensorLeft, SensorUltrasonic sensorForward, SensorUltrasonic sensorRight) {
  int distanceLeft = sensorLeft.getPreviousRead();
  int distanceForward = sensorForward.getPreviousRead();
  int distanceRight = sensorRight.getPreviousRead();

  // avoidance vectors for each sensor
  float thetaLeft = sensorLeft.theta - PI + TWO_PI;
  float thetaForward = sensorForward.theta + PI;
  float thetaRight = sensorRight.theta + PI - TWO_PI;

  float distanceInverseLeft = 1.0 / distanceLeft;
  float distanceInverseForward = 1.0 / distanceForward;
  float distanceInverseRight = 1.0 / distanceRight;
  float distanceInverseSum = distanceInverseLeft + distanceInverseForward + distanceInverseRight;

  float weightLeft = distanceInverseLeft / distanceInverseSum;
  float weightForward = distanceInverseForward / distanceInverseSum;
  float weightRight = distanceInverseRight / distanceInverseSum;

  float yHatLeft = thetaLeft * weightLeft;
  float yHatForward = thetaForward * weightForward;
  float yHatRight = thetaRight * weightRight;

  return yHatLeft + yHatForward + yHatRight;
}

float constrainAngle (float angle) {
  angle = fmod(angle + PI, TWO_PI);
  if (angle < 0) {
    angle += TWO_PI;
  }
  return angle - PI;
}

bool flagObstacleAvoidance = false;
float thetaDesired = 0;
void Robot::stepObstacleAvoidance() {
  int distanceThresholdDanger = 8;
  int distanceThresholdEnter = 12;
  int distanceThresholdExit = 18;

  int distanceLeft = sensorLeft.getPreviousRead();
  int distanceForward = sensorForward.getPreviousRead();
  int distanceRight = sensorRight.getPreviousRead();

  int distanceLeast = distanceLeft;
  if (distanceLeast > distanceForward) distanceLeast = distanceForward;
  if (distanceLeast > distanceRight) distanceLeast = distanceRight;

  if (flagObstacleAvoidance == false) {
    flagObstacleAvoidance = distanceLeast < distanceThresholdEnter;
    if (flagObstacleAvoidance == true) {
      thetaDesired = getThetaDesired(sensorLeft, sensorForward, sensorRight);
      thetaDesired = constrainAngle(thetaDesired);

      Serial.print("Obstacle avoidance system begin: ");
      Serial.println(thetaDesired);
    }
  } else {
    flagObstacleAvoidance = distanceLeast < distanceThresholdExit;
    if (flagObstacleAvoidance == false) {
      thetaDesired = 0;
      Serial.println("Obstacle avoidance system end");
    }
  }

  if (flagObstacleAvoidance == true) {
    float velocity = velocitySlow;
    float errorTheta = thetaDesired - theta;
    float omega = regulatorObstacleAvoidanceOmega.Compute(theta, thetaDesired);
    // float omega = thetaDesired - theta;

    if (distanceLeast < distanceThresholdDanger) {
      velocity = -velocitySlow;
    } else if (distanceLeast >= distanceThresholdDanger && distanceLeast < distanceThresholdEnter) {
      velocity = 0;
    }

    if (abs(errorTheta) > PI / 2) {
      velocity = 0;
      omega /= 2;
    } else if (abs(errorTheta) > PI / 4) {
      velocity /= 2;
      omega /= 2;
    }

    targetVelocityLeft = (2*velocity + omega*wheelAxelLength)/(2*wheelRadius);
    targetVelocityRight = (2*velocity - omega*wheelAxelLength)/(2*wheelRadius);
  } else {
    //regulatorObstacleAvoidanceOmega.Compute(0, 0);
  }
}
