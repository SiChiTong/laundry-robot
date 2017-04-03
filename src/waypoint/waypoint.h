#ifndef WAYPOINT_H
#define WAYPOINT_H

class Waypoint {
  private:
    float x = 0;
    float y = 0;
    float threshold = 3;

  public:
    float getX();
    float getY();
    float getThetaDesired(float, float);
    float getErrorDistance(float, float);
    void setXY(float, float);
    bool isComplete(float, float);

    Waypoint();
    Waypoint(float, float);
    ~Waypoint();
};

#endif