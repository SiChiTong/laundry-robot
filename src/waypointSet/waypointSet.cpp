#include "waypoint/waypoint.h"
#include "waypointSet/waypointSet.h"

WaypointSet::WaypointSet() {
  waypoints[0] = Waypoint(0, 0);
  waypoints[1] = Waypoint(12, 72);
  waypoints[2] = Waypoint(-36, 36);
  waypoints[3] = Waypoint(0, 0);
}

WaypointSet::~WaypointSet() {

}

void WaypointSet::reset() {
  index = 0;
}

bool WaypointSet::step(float agentX, float agentY) {
  Waypoint currentWaypoint = waypoints[index];
  bool isComplete = currentWaypoint.isComplete(agentX, agentY);
  if (isComplete == true) {
    next();
  }
  return isComplete;
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

bool WaypointSet::isComplete() {
  return (index + 1 == count);
}
