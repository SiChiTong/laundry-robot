#ifndef ROBOT_H
#define ROBOT_H
#include <Arduino.h>
#include "IRremote.h"
#include "pid/pid.h"
#include "motor/motor.h"
#include "sensorUltrasonic/sensorUltrasonic.h"
#include "waypointSet/waypointSet.h"

class Robot {
  private:
    // actual velocity (ticks per 50 ms)
    double velocityLeft = 0;
    double velocityRight = 0;

    // target velocities of motors (ticks per 50 ms)
    double targetVelocityLeft = 0;
    double targetVelocityRight = 0;

    // current position of robot
    float x = 0;
    float y = 0;
    double theta = 0; // angle of robot (in radians)

    WaypointSet waypointSet = WaypointSet();
    bool autonomousMode = false;

    // robot measurements
    float wheelRadius = 2.5; // inches
    float wheelAxelLength = 17; // inches

    // private step functions
    void readSensors();
    void stepNavigation();
    void stepObstacleBoundaryFollow();
    void stepObstacleAvoidance();
    void stepBumpers();
    void stepRemote();
    void stepMotors();

  public:
    IRrecv sensorIR = IRrecv(11);
    SensorUltrasonic sensorForward = SensorUltrasonic(50, 51);
    SensorUltrasonic sensorLeft = SensorUltrasonic(53, 52);
    SensorUltrasonic sensorRight = SensorUltrasonic(48, 49);
    Motor motorLeft = Motor(2, 24, 25);
    Motor motorRight = Motor(3, 23, 22);

    //PID Regulators
    PID regulatorMotorLeft = PID(7, 8, 0, DIRECT);
    PID regulatorMotorRight = PID(7, 8, 0, DIRECT);
    PID regulatorNavigationOmega = PID(5, 0.5, 0, DIRECT);
    PID regulatorObstacleAvoidanceOmega = PID(5, 0.5, 0, DIRECT);

    // velocities (ticks per 50 ms)
    float velocityFast = 20;
    float velocityModerate = 15;
    float velocitySlow = 7;

    // instance functions
    void setUp();
    void step();
    void printStats();

    // wheel encoder handlers. these have to be static :(
    static void handleEncoderTickLeft();
    static void handleEncoderTickRight();

    // update stats functions that are called toward end of step()
    void updateOdometry();
    void updateThetaDesired();

    Robot();
    ~Robot();
};

#endif
