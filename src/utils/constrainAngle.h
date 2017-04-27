#include "utils/utils.h"

static float constrainAngle (float _angle) {
  float angle = _angle;

  // loop until angle within -PI and PI
  while (1) {
    if (angle < -PI) {
      angle += TWO_PI;
    } else if (angle > PI) {
      angle -= TWO_PI;
    } else {
      break;
    }
  }

  return angle;
}
