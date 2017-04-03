#ifndef SENSOR_H
#define SENSOR_H

class SensorUltrasonic {
  private:
    int triggerPin;
    int echoPin;
    int distanceInches;

  public:
    void setUp();
    void initializePins();
    int getPreviousRead();
    int readDistanceInches();
    SensorUltrasonic(int, int);
    ~SensorUltrasonic();
};

#endif
