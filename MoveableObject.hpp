#ifndef MOVEABLEOBJECT_HPP
#define MOVEABLEOBJECT_HPP

#include <iostream>

#include "Object.hpp"

class MoveableObject : public Object
{
protected:
  float speed;
  float dx, dy;

public:
  MoveableObject(float x, float y, const std::string &filename);
  MoveableObject(float x, float y, float dx, float dy, float speed, const std::string &filename);
  MoveableObject(const Object &obj);
  MoveableObject(float dx, float dy, float speed, const Object &obj);

  void setVector(float dx, float dy);
  void setSpeed(float speed);

  float getDx() const;
  float getDy() const;
  float getSpeed() const;

  void move();
  void selfRotation(float x, float y, float theta); // TODO
  void selfDilated(float x, float y, float k); // TODO
};

#endif