#include <Arduino.h>

#include "globals.h"
#include "robot/robot.h"

Robot robot;

void setup() {
  Serial.begin(115200);
  robot.setUp();
}

void loop() {
  robot.printStats();
  for (int i = 0; i < 50; i++) {
    robot.step();
  }
}
