#include <Arduino.h>

#include "globals.h"
#include "robot/robot.h"

Robot robot;

void setup() {
  Serial.begin(115200);
  robot.setUp();
}

void loop() {
  for (int i = 0; i < 10; i++) {
    robot.step();
  }
  robot.printStats();

  // robot.motorLeft.step(0);
  // robot.motorRight.step(0);
  // delay(10000);
}
