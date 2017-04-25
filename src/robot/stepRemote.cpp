#include "robot/robot.h"

static decode_results results;
static int manualStepCount = 0;
static float manualPwmLeft = 0;
static float manualPwmRight = 0;
float manualPwm = 85;
bool flagRemote = false;
bool lastFlagRemote = false;

void Robot::stepRemote() {
  if (sensorIR.decode(&results)) {
    switch(results.value) {
      case 0xFF02FD: // ok -> stop
        Serial.println("STOP");
        flagRemote = true;
        manualStepCount = 0;
        manualPwmLeft = 0;
        manualPwmRight = 0;
        break;
      case 0xFF629D: // forward
        flagRemote = true;
        manualStepCount = 0;
        manualPwmLeft = manualPwm;
        manualPwmRight = manualPwm;
        break;
      case 0xFF22DD: // left
        flagRemote = true;
        manualStepCount = 0;
        manualPwmLeft = -manualPwm;
        manualPwmRight = manualPwm;
        break;
      case 0xFFC23D: // right
        flagRemote = true;
        manualStepCount = 0;
        manualPwmLeft = manualPwm;
        manualPwmRight = -manualPwm;
        break;
      case 0xFFA857: // reverse
        flagRemote = true;
        manualStepCount = 0;
        manualPwmLeft = -manualPwm;
        manualPwmRight = -manualPwm;
        break;
      case 0xFF6897: // 1
        manualPwm = 45;
        Serial.println("Manual speed changed to 45%");
        break;
      case 0xFF9867: // 2
        manualPwm = 65;
        Serial.println("Manual speed changed to 65%");
        break;
      case 0xFFB04F: // 3
        manualPwm = 80;
        Serial.println("Manual speed changed to 80%");
        break;
      case 0xFF30CF: Serial.println("4");    break;
      case 0xFF18E7: Serial.println("5");    break;
      case 0xFF7A85: Serial.println("6");    break;
      case 0xFF10EF: Serial.println("7");    break;
      case 0xFF38C7: Serial.println("8");    break;
      case 0xFF5AA5: Serial.println("9");    break;
      case 0xFF4AB5: Serial.println("0");    break;
      case 0xFF52AD: // # -> reset odometry and navigation
        x = 0;
        y = 0;
        theta = 0;
        waypointSet.reset();
        flagRemote = true;
        manualStepCount = 3;
        Serial.println("Reset navigation and odometry");
        break;
      case 0xFF42BD: // * -> toggle autonomous/manual mode
        flagRemote = !flagRemote;
        break;
      case 0xFFFFFFFF: // repeat previous command
        manualStepCount = 0;
        break;
      default:
        Serial.print("Could not read IR command: ");
        Serial.println(results.value, HEX);
    }

    sensorIR.resume();
  }

  if (flagRemote == true) {
    regulatorMotorLeft.Compute(0, 0);
    regulatorMotorRight.Compute(0, 0);
  }

  if (flagRemote == true && manualStepCount < 3) {
    manualStepCount++;
    flagRemote = true;
    motorLeft.step(manualPwmLeft);
    motorRight.step(manualPwmRight);
  } else if (flagRemote == true) {
    flagRemote = true;
    motorLeft.step(0);
    motorRight.step(0);
  } else {
    flagRemote = false;
  }

  bool flagSet = (!lastFlagRemote && flagRemote);
  bool flagRemove = (lastFlagRemote && !flagRemote);

  // set flag or release flag
  if (flagSet) {
    requestFlagChange(FLAG_REMOTE);
  } else if (flagRemove) {
    resetFlag();
  }

  lastFlagRemote = flagRemote;
}
