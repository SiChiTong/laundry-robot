#include "robot/robot.h"
#include "utils/utils.h"

void Robot::updateOdometry() {
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
  theta -= (distanceRight - distanceLeft) / wheelAxelLength;

  theta = constrainAngle(theta);
}
