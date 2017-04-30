#include "robot/robot.h"
#include "utils/utils.h"

void Robot::updateKinematics() {
  // imu calibration readings
  uint8_t calibrationImu, calibrationGyro, calibrationAccel, calibrationMag;
  calibrationImu = calibrationGyro = calibrationAccel = calibrationMag = 0;
  imu.getCalibration(&calibrationImu, &calibrationGyro, &calibrationAccel, &calibrationMag);

  int ticksPerRevolution = 192;

  // change in ticks from last check
  int tickDeltaLeft = motorLeft.getEncoderTickCountDelta();
  int tickDeltaRight = motorRight.getEncoderTickCountDelta();

  // distance moved given # of wheel ticks and wheel radius
  float distanceLeft = 2.0 * PI * wheelRadius * ((float)tickDeltaLeft / ticksPerRevolution);
  float distanceRight = 2.0 * PI * wheelRadius * ((float)tickDeltaRight / ticksPerRevolution);
  float distanceCenter = (distanceLeft + distanceRight) / 2.0;

  // determine XY coordinates of center of robot and theta (angle)
  x = x + distanceCenter * sin(theta);
  y = y + distanceCenter * cos(theta);

  if (calibrationImu >= 0) {
    // set theta to imu reading if calibrated
    sensors_event_t event;
    imu.getEvent(&event);

    // convert to radians and set between -PI and PI
    float thetaDegrees = event.orientation.x;
    float thetaRadians = thetaDegrees * PI / 180;
    if (thetaRadians > PI) thetaRadians -= TWO_PI;
    else if (thetaRadians < -PI) thetaRadians += TWO_PI;
    theta = thetaRadians;
  } else {
    // use wheel odometry readings to estimate theta
    theta -= (distanceRight - distanceLeft) / wheelAxelLength;

    Serial.print("IMU not calibrated. Sys:");
    Serial.print(calibrationImu, DEC);
    Serial.print(" G:");
    Serial.print(calibrationGyro, DEC);
    Serial.print(" A:");
    Serial.print(calibrationAccel, DEC);
    Serial.print(" M:");
    Serial.println(calibrationMag, DEC);
  }

  theta = constrainAngle(theta);
}
