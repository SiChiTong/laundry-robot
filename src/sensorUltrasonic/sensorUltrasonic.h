#ifndef SENSOR_H
#define SENSOR_H

class SensorUltrasonic {
  private:
    int triggerPin;
    int echoPin;
    int distanceInches;

  public:
    float theta;
    void setUp();
    void initializePins();
    int getPreviousRead();
    int readDistanceInches();
    SensorUltrasonic(int, int);
    ~SensorUltrasonic();
};

#endif
