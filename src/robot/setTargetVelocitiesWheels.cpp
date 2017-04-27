#include "robot/robot.h"

void Robot::setTargetVelocitiesWheels() {
  float totalVelocity = 1;

  float sum = abs(velocity) + abs(omega);
  float percentVelocity = abs(velocity) / sum;
  float percentOmega = abs(omega) / sum;

  if (velocity < 0) percentVelocity *= -1;
  if (omega < 0) percentOmega *= -1;

  // scale values down to total velocity
  float velocityScaled = totalVelocity * percentVelocity;
  float omegaScaled = totalVelocity * percentOmega;

  targetVelocityLeft = (2*velocityScaled + omegaScaled*wheelAxelLength)/(2*wheelRadius);
  targetVelocityRight = (2*velocityScaled - omegaScaled*wheelAxelLength)/(2*wheelRadius);
}
