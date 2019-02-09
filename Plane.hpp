#ifndef PLANE_HPP
#define PLANE_HPP

#include <vector>

#include "Line.hpp"
using namespace std;

class Plane
{
  protected:
    Pixel position;
    vector<Line> lines;

    int width;
    int height;

    int color;
    int priority;

  public:
    Plane();
    Plane(float x, float y, vector<Line> lines, int color, int priority);

    bool outOfWindow(int height, int width) const;
    void reverseHorizontal();

    void setPos(Pixel position);
    void setPos(float x, float y);
    void setNLine(int nline);
    void setColor(int color);
    void setPriority(int priority);
    void setWidth();
    void setHeight();

    int getColor() const;
    int getPriority() const;
    int getWidth() const;
    int getHeight() const;

    vector<Line> getLines() const;
    Pixel getPos() const;

    const vector<Line> &getRefLines() const;
    const Pixel &getRefPos() const;

    /* For MovableObject polymorphism purpose */
    void move();
    void selfRotation(float pivotX, float pivotY, float theta);
    void selfDilated(float pivotX, float pivotY, float scalingConstant);
};

#endif