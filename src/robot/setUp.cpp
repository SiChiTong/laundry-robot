#include "robot/robot.h"

void Robot::setUp() {
  attachInterrupt(digitalPinToInterrupt(18), handleEncoderTickLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(19), handleEncoderTickRight, RISING);

  regulatorMotorLeft.SetMode(AUTOMATIC);
  regulatorMotorLeft.SetSampleTime(50);
  regulatorMotorLeft.SetOutputLimits(-100, 100);

  regulatorMotorRight.SetMode(AUTOMATIC);
  regulatorMotorRight.SetSampleTime(50);
  regulatorMotorRight.SetOutputLimits(-100, 100);

  regulatorNavigationOmega.SetMode(AUTOMATIC);
  regulatorNavigationOmega.SetSampleTime(50);
  regulatorNavigationOmega.SetOutputLimits(-1, 1);

  regulatorObstacleBoundaryFollowOmega.SetMode(AUTOMATIC);
  regulatorObstacleBoundaryFollowOmega.SetSampleTime(50);
  regulatorObstacleBoundaryFollowOmega.SetOutputLimits(-1, 1);

  regulatorObstacleAvoidanceOmega.SetMode(AUTOMATIC);
  regulatorObstacleAvoidanceOmega.SetSampleTime(50);
  regulatorObstacleAvoidanceOmega.SetOutputLimits(-1, 1);

  // keep values between 0 and TWO_PI for accurate
  // desired theta calculations
  sensorLeftLeft.theta = -PI / 2;
  sensorLeft.theta = -PI / 4;
  sensorForward.theta = 0;
  sensorRight.theta = PI / 4;
  sensorRightRight.theta = PI / 2;

  sensorIR.enableIRIn();
  sensorLeftLeft.setUp();
  sensorLeft.setUp();
  sensorForward.setUp();
  sensorRight.setUp();
  sensorRightRight.setUp();
  motorLeft.setUp();
  motorRight.setUp();
}
