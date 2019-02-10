#ifndef PLANE_HPP
#define PLANE_HPP

#include <vector>

#include "Line.hpp"
using namespace std;

class Plane
{
  protected:
    vector<Line> lines;

    float xMin, yMin, xMax, yMax;

    int color;
    int priority;

  public:
    Plane(const vector<Line> &lines, int color, int priority);

    void reverseHorizontal();

    void setColor(int color);
    void setPriority(int priority);
    virtual void calculate();

    int getColor() const;
    int getPriority() const;
    int getWidth() const;
    int getHeight() const;

    vector<Line> getLines() const;

    const vector<Line> &getRefLines() const;

    /* For MovableObject polymorphism purpose */
    virtual void selfRotation(float pivotX, float pivotY, float theta);
    virtual void selfDilated(float pivotX, float pivotY, float scalingConstant);
};

#endif