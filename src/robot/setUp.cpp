#include "robot/robot.h"

void Robot::setUp() {
  attachInterrupt(digitalPinToInterrupt(18), handleEncoderTickLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(19), handleEncoderTickRight, RISING);

  regulatorMotorLeft.SetMode(AUTOMATIC);
  regulatorMotorLeft.SetSampleTime(25);
  regulatorMotorLeft.SetOutputLimits(-100, 100);

  regulatorMotorRight.SetMode(AUTOMATIC);
  regulatorMotorRight.SetSampleTime(25);
  regulatorMotorRight.SetOutputLimits(-100, 100);

  regulatorNavigationOmega.SetMode(AUTOMATIC);
  regulatorNavigationOmega.SetSampleTime(25);
  regulatorNavigationOmega.SetOutputLimits(-6, 6);

  regulatorObstacleAvoidanceOmega.SetMode(AUTOMATIC);
  regulatorObstacleAvoidanceOmega.SetSampleTime(25);
  regulatorObstacleAvoidanceOmega.SetOutputLimits(-3, 3);

  sensorLeft.theta = -PI / 4;
  sensorForward.theta = 0;
  sensorRight.theta = PI / 4;

  sensorIR.enableIRIn();
  sensorForward.setUp();
  sensorRight.setUp();
  sensorLeft.setUp();
  motorLeft.setUp();
  motorRight.setUp();
}
