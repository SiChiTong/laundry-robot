#include <Arduino.h>

#include "sensorUltrasonic/sensorUltrasonic.h"

const float tempOfAirCelcius = 23;
const float speedOfSoundMS = 331.3 + (0.606 * tempOfAirCelcius); // meters per second

SensorUltrasonic::SensorUltrasonic(int triggerPin, int echoPin) {
  triggerPin = triggerPin;
  echoPin = echoPin;
}

SensorUltrasonic::~SensorUltrasonic() {
  
}

void SensorUltrasonic::setUp() {
  pinMode(this->triggerPin, OUTPUT);
  pinMode(this->echoPin, INPUT);
}

int SensorUltrasonic::getPreviousRead() {
  return distanceInches;
}

int SensorUltrasonic::readDistanceInches() {
  // Making sure the trigPin is clear for use
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  // Generate ultrasound wave
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // "HIGH" given meaning it will wait for HIGH voltage to begin
  // and time until the HIGH signal ends.
  int duration = pulseIn(echoPin, HIGH, 25000);
  if (duration == 0) {
    duration = 23000;
  }

  // Multiply duration by speed of sound factor,
  // then divide by 2 since it count the travel time
  // to and from the endpoint.
  float distanceCm = duration / 20000.0 * speedOfSoundMS;
  distanceInches = distanceCm * 0.393701;
  return distanceInches;
}
