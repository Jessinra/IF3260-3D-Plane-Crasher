#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Color.hpp"
#include "Plane.hpp"
#include "Line.hpp"
#include "Pixel.hpp"
#include "MoveablePlane.hpp"

class Object
{
  protected:
    Pixel position;
    int nPlane;
    vector<Plane*> planes;
    int width;
    int height;

  public:
    Object();
    Object(float x, float y, std::string filename);

    void setPos(Pixel position);
    void setPos(float x, float y);
    void setNPlane(int nPlane);

    void setWidth();  // TODO
    void setHeight(); // TODO

    vector<Plane*> getPlanes() const;
    Pixel getPos() const;
    int getNPlane() const;
    int getWidth() const;
    int getHeight() const;

    const vector<Plane*> &getRefPlanes() const;
    const Pixel &getRefPos() const;

    void reverseHorizontal(); // TODO
    bool outOfWindow(int height, int width) const;
};

#endif