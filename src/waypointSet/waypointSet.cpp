#include "waypoint/waypoint.h"
#include "waypointSet/waypointSet.h"

WaypointSet::WaypointSet() {
  waypoints[0] = Waypoint(0*12, 5*12);
  waypoints[1] = Waypoint(0*12, 5*12);
  waypoints[2] = Waypoint(0*12, 5*12);
  waypoints[3] = Waypoint(0*12, 5*12);
}

WaypointSet::~WaypointSet() {

}

void WaypointSet::reset() {
  index = 0;
}

bool WaypointSet::step(float agentX, float agentY) {
  Waypoint currentWaypoint = waypoints[index];
  bool isCurrentWaypointComplete = currentWaypoint.isComplete(agentX, agentY);
  if (isCurrentWaypointComplete == true) {
    if (isComplete(agentX, agentY) == false) {
      Serial.print("Waypoint reached: ");
      Serial.print(currentWaypoint.getX());
      Serial.print(", ");
      Serial.println(currentWaypoint.getY());
    }
    next();
  }
  return isCurrentWaypointComplete;
}

int WaypointSet::getWaypointCount() {
  return count;
}

void WaypointSet::next() {
  if (index + 1 < count) {
    index++;
  }
}

float WaypointSet::getThetaDesired(float agentX, float agentY) {
  Waypoint currentWaypoint = waypoints[index];
  return currentWaypoint.getThetaDesired(agentX, agentY);
}

float WaypointSet::getErrorDistance(float agentX, float agentY) {
  Waypoint currentWaypoint = waypoints[index];
  return currentWaypoint.getErrorDistance(agentX, agentY);
}

bool WaypointSet::isComplete(float agentX, float agentY) {
  Waypoint currentWaypoint = waypoints[index];
  bool isCompleteArray = (index + 1 == count);
  bool isCompleteWaypoint = currentWaypoint.isComplete(agentX, agentY);
  return isCompleteArray && isCompleteWaypoint;
}
