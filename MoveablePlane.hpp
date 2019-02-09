#ifndef MOVEABLE_PLANE_HPP
#define MOVEABLE_PLANE_HPP

#include "Plane.hpp"
using namespace std;

class MoveablePlane : public Plane
{
protected:
  float speed;
  float dx, dy;

public:
  MoveablePlane(float x, float y, int nline, vector<Line> lines, int color, int priority);
  MoveablePlane(float x, float y, float dx, float dy, float speed, int nline, vector<Line> lines, int color, int priority);
  MoveablePlane(const Plane &plane);
  MoveablePlane(float dx, float dy, float speed, const Plane &plane);

  void setVector(float dx, float dy);
  void setSpeed(float speed);

  float getDx() const;
  float getDy() const;
  float getSpeed() const;

  void move();
  void selfRotation(float pivotX, float pivotY, float theta);
  void selfDilated(float pivotX, float pivotY, float scalingConstant);
};

#endif