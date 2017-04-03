#include <Arduino.h>

#include "globals.cpp"
#include "robot/robot.h"

void setup() {
  Serial.begin(9600);
  robot.setUp();
}

void loop() {
  robot.printStats();
  for (int i = 0; i < 25; i++) {
    robot.step();
  }
}
