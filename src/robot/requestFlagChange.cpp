#include "robot/robot.h"
#include "utils/utils.h"

void Robot::requestFlagChange(int newFlag) {
  // new flag must be higher priority
  if (newFlag < flag) {
    flag = newFlag;

    switch (flag) {
      case FLAG_SYSTEM_COMPLETE:
        Serial.println("Control system complete");
        break;
      case FLAG_REMOTE:
        Serial.println("Control system subsumed by remote subsystem");
        break;
      case FLAG_BUMPER:
        Serial.println("Control system subsumed by bumper subsystem");
        break;
      case FLAG_AVOID_OBSTACLE:
        Serial.println("Control system subsumed by avoid obstacle subsystem");
        break;
      case FLAG_FOLLOW_BOUNDARY:
        Serial.println("Control system subsumed by follow boundary subsystem");
        break;
      case FLAG_NAVIGATION:
        Serial.println("Control system subsumed by navigation subsystem");
        break;
      default:
        Serial.println("Control system subsumed by unknown subsystem");
        break;
    }
  }
}
