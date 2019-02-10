#ifndef MOVEABLE_PLANE_HPP
#define MOVEABLE_PLANE_HPP

#include "Plane.hpp"
using namespace std;

class MoveablePlane : public Plane
{
protected:
  Pixel position;

public:
  MoveablePlane(float x, float y, const vector<Line> &lines, int color, int priority);
  MoveablePlane(float x, float y, const Plane &plane);
  
  void setPos(Pixel position);
  void setPos(float x, float y);
  
  Pixel getPos() const;
  const Pixel &getRefPos() const;
  void calculate() override;

  void selfRotation(float pivotX, float pivotY, float theta);
  void selfDilated(float pivotX, float pivotY, float scalingConstant);
};

#endif