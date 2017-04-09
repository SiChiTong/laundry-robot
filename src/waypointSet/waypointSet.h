#ifndef WAYPOINTSET_H
#define WAYPOINTSET_H
#include "waypoint/waypoint.h"

class WaypointSet {
  private:
    int index = 0;
    int count = 3;
    Waypoint* waypoints = new Waypoint[count];
    void next();

  public:
    int getWaypointCount();
    void reset();
    bool step(float, float);
    bool isComplete(float, float);
    float getThetaDesired(float, float);
    float getErrorDistance(float, float);

    WaypointSet();
    ~WaypointSet();
};

#endif
