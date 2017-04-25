#include "robot/robot.h"

void Robot::setTargetVelocitiesWheels(float velocity, float omega) {
  float maxTotalVelocity = 1;
  float sum = velocity + omega;
  if (sum > maxTotalVelocity || sum < -maxTotalVelocity) {
    float percentVelocity = velocity / sum;
    float percentOmega = omega / sum;

    // scale values down to max velocity
    velocity *= maxTotalVelocity * percentVelocity;
    omega *= maxTotalVelocity * percentOmega;

    targetVelocityLeft = (2*velocity + omega*wheelAxelLength)/(2*wheelRadius);
    targetVelocityRight = (2*velocity - omega*wheelAxelLength)/(2*wheelRadius);
  } else {
    targetVelocityLeft = (2*velocity + omega*wheelAxelLength)/(2*wheelRadius);
    targetVelocityRight = (2*velocity - omega*wheelAxelLength)/(2*wheelRadius);
  }
}
