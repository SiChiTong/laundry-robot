#include <Arduino.h>
#include "waypoint/waypoint.h"

Waypoint::Waypoint() {

}

Waypoint::Waypoint(float _x, float _y) {
  setXY(_x, _y);
}

Waypoint::~Waypoint() {

}

void Waypoint::setXY(float _x, float _y) {
  x = _x;
  y = _y;
}

float Waypoint::getX() {
  return x;
}

float Waypoint::getY() {
  return y;
}

float Waypoint::getThetaDesired(float agentX, float agentY) {
  float errorX = x - agentX;
  float errorY = y - agentY;
  return PI/2 - atan2(errorY, errorX);
}

float Waypoint::getErrorDistance(float agentX, float agentY) {
  float errorX = x - agentX;
  float errorY = y - agentY;
  return sqrt(errorX * errorX + errorY * errorY);
}

bool Waypoint::isComplete(float agentX, float agentY) {
  float error = getErrorDistance(agentX, agentY);
  return error < threshold;
}
