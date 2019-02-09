#ifndef POINT_HPP
#define POINT_HPP

#include <vector>
#define PI 3.14159265
using namespace std;

class Pixel
{
  private:
    float x;
    float y;
    unsigned int color;

  public:
    Pixel();
    Pixel(float x, float y);
    Pixel(float x, float y, unsigned int color);

    float getX() const;
    float getY() const;
    unsigned int getColor() const;

    void setX(float x);
    void setY(float y);
    void setPos(float x, float y);
    void setColor(unsigned int color);
    
    Pixel rotation(float pivotX, float pivotY, float theta);
    Pixel dilated(float pivotX, float pivotY, float scalingConstant);
};

#endif