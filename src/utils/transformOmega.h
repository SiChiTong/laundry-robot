#include "utils/utils.h"

static float transformOmega (float thetaCurrent, float thetaDesired) {
  // transform (see https://www.youtube.com/watch?v=sSIJ3qoy52Q)
  float velocityPlanned = 1;
  float u1 = velocityPlanned * cos(thetaDesired); // desired velocity in x direction
  float u2 = velocityPlanned * sin(thetaDesired); // desired velocity in y direction
  float l = 8; // distance between x,y tilde and x,y
  float phi = thetaCurrent; // robot's theta

  // matrix multiplication of 1/l identiy matrix, inverse rotation matrix, and u1, u2 matrix
  float velocity = cos(-phi) * u1 - sin(-phi) * u2;
  float omega = (1.0 / l) * sin(-phi) * u1 + (1.0 / l) * cos(-phi) * u2;

  // |velocity| = 1
  if (velocity >= 0) velocity = 1;
  else if (velocity < 0) velocity = -1;

  // omega between 1 and -1
  if (omega > 1) omega = 1;
  else if (omega < -1) omega = -1;

  return omega;
}
