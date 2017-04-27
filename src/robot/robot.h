#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "IRremote.h"
#include "robot/flags.h"
#include "pid/pid.h"
#include "motor/motor.h"
#include "sensorUltrasonic/sensorUltrasonic.h"
#include "waypointSet/waypointSet.h"

class Robot {
  private:
    // actual velocity (ticks per 50 ms)
    double velocity = 0;
    double omega = 0;
    double velocityLeft = 0;
    double velocityRight = 0;

    // target velocities of motors (ticks per 50 ms)
    double targetVelocityLeft = 0;
    double targetVelocityRight = 0;
    double thetaDesired = 0;

    // current position of robot
    float x = 0;
    float y = 0;
    double theta = 0; // angle of robot (in radians)

    WaypointSet waypointSet = WaypointSet();

    // robot measurements
    float wheelRadius = 2.83465; // inches
    float wheelAxelLength = 17; // inches

    // private instance methods
    void setTargetVelocitiesWheels();
    void readSensors();

    // theta calculations
    float getThetaDesiredNavigation();
    float getThetaDesiredObstacleBoundaryFollow(bool);
    float getThetaDesiredAvoidObstacle(float);

    // flags
    int flag = FLAG_REMOTE;
    void setFlagRemote();
    void setFlagObstacleAvoidance();
    void setFlagObstacleBoundaryFollow();
    void setFlagNavigation();
    void resetFlag();
    void requestFlagChange(int);

    // step subsystems
    void stepNavigation();
    void stepObstacleBoundaryFollow();
    void stepObstacleAvoidance();
    void stepBumpers();
    void stepRemote();
    void stepMotors();

  public:
    IRrecv sensorIR = IRrecv(11);
    SensorUltrasonic sensorLeftLeft = SensorUltrasonic(45, 44);
    SensorUltrasonic sensorLeft = SensorUltrasonic(53, 52);
    SensorUltrasonic sensorForward = SensorUltrasonic(50, 51);
    SensorUltrasonic sensorRight = SensorUltrasonic(48, 49);
    SensorUltrasonic sensorRightRight = SensorUltrasonic(47, 46);
    Motor motorLeft = Motor(2, 24, 25);
    Motor motorRight = Motor(3, 23, 22);

    // PID Regulators
    PID regulatorMotorLeft = PID(12, 1, 5, DIRECT);
    PID regulatorMotorRight = PID(12, 1, 5, DIRECT);

    // instance functions
    void setUp();
    void step();
    void printStats();
    float getX();
    float getY();
    WaypointSet getWaypointSet();
    bool isObstacleDetected(float);

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
