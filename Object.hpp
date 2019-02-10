#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "Plane.hpp"
#include "MoveablePlane.hpp"
using namespace std;

class Object
{
  protected:
    Point position;
    vector<MoveablePlane> planes;

    float xMin, yMin, xMax, yMax;

    int nPlane;
    int width;
    int height;

  public:
    Object();
    Object(float x, float y, std::string filename);

    void setPos(Pixel position);
    void setPos(float x, float y);
    void setNPlane(int nPlane);

    void calculate();

    vector<MoveablePlane> getPlanes() const;
    Point getPos() const;
    int getNPlane() const;
    int getWidth() const;
    int getHeight() const;

    vector<MoveablePlane> & getRefPlanes();
    const vector<MoveablePlane> & getConstRefPlanes() const;
    const Point&getRefPos() const;

    void reverseHorizontal(); // TODO
    bool outOfWindow(int height, int width) const;
};

#endif