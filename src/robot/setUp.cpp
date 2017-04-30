#include "robot/robot.h"

void Robot::setUp() {
  attachInterrupt(digitalPinToInterrupt(18), handleEncoderTickLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(19), handleEncoderTickRight, RISING);

  if(!imu.begin()) {
    Serial.println("Error: BNO055 connection failed.");
  } else {
    imu.setExtCrystalUse(true);
  }

  regulatorMotorLeft.SetMode(AUTOMATIC);
  regulatorMotorLeft.SetSampleTime(50);
  regulatorMotorLeft.SetOutputLimits(-10, 10);

  regulatorMotorRight.SetMode(AUTOMATIC);
  regulatorMotorRight.SetSampleTime(50);
  regulatorMotorRight.SetOutputLimits(-10, 10);

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
