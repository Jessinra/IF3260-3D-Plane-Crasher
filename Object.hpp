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

class Object
{
    // Suatu object tersusun atas garix matrix of pixel

  protected:
    Pixel position;
    int nplane;
    vector<Plane> planes;

  public:
    Object();
    Object(float, float, std::string);

    void setPos(Pixel); // change setPos to void
    void setPos(float, float);
    void setNPlane(int);

    vector<Plane> getPlanes() const;
    Pixel getPos() const;
    int getNPlane() const;
    const vector<Plane> &getRefPlanes() const;
    const Pixel &getRefPos() const;
};

#endif