#include "utils/utils.h"

static float constrainAngle (float _angle) {
  float angle = fmod(_angle + PI, TWO_PI);

  if (angle < 0) {
    angle += PI;
  } else {
    angle -= PI;
  }

  if (angle == -PI && _angle > 0) {
    angle = PI;
  }

  return angle;
}
