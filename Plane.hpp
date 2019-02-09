#ifndef PLANE_HPP
#define PLANE_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Color.hpp"
#include "Line.hpp"
#include "Pixel.hpp"

class Plane
{
    // Suatu plane (bidang) tersusun atas garix matrix of pixel

  protected:
    Pixel position;
    vector<Line> lines;
    int width;
    int height;
    int nline;
    int col;

  public:
    Plane();
    Plane(float, float, int, vector<Line>, int);

    bool outOfWindow(int, int) const;
    void reverseHorizontal();

    void setPos(Pixel); // change setPos to void
    void setPos(float, float);
    void setNLine(int);
    void setColor(int);

    int getNLine() const;
    int getColor() const;
    vector<Line> getLines() const;
    Pixel getPos() const;
    int getWidth() const;
    int getHeight() const;
    const vector<Line> &getRefLines() const;
    const Pixel &getRefPos() const;
};

#endif