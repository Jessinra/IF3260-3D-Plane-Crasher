
#include "Plane.hpp"

Plane::Plane()
{
}

Plane::Plane(float x, float y, int nline, vector<Line> lines, int color)
{
    setPos(x, y);
    this->lines = lines;
    this->col = color;
    this->nline = nline;
    

    int xStart, yStart, xEnd, yEnd;
    int xMin, xMax, yMin, yMax;
    Pixel pxl;

    for (int i = 0; i < this->nline; ++i)
    {
        pxl = lines[i].getStartPixel;
        xStart = pxl.getX;
        yStart = pxl.getY;
        pxl = lines[i].getEndPixel;
        xEnd = pxl.getX;
        yEnd = pxl.getY;
        
        if (i == 0)
        {
            xMin = min(xStart, xEnd);
            xMax = max(xStart, xEnd);
            yMin = min(yStart, yEnd);
            yMax = max(yStart, yEnd);
        }
        else
        {
            xMin = min(yMin, min(xStart, xEnd));
            xMax = max(xMax, max(xStart, xEnd));
            yMin = min(yMin, min(yStart, yEnd));
            yMax = max(yMax, max(yStart, yEnd));
        }
    }
    this->height = yMax + 1;
    this->width = xMax + 1;
}

bool Plane::outOfWindow(int h, int w) const
{
    return (this->position.getX() >= w || this->position.getY() >= h || this->position.getX() <= -width || this->position.getY() <= -height);
}

void Plane::reverseHorizontal(){
    for(Line &line : lines){
        line.setStartPixel(Pixel(width - line.getStartPixel().getX() - 1, line.getStartPixel().getY(), line.getStartPixel().getColor()));
        line.setEndPixel(Pixel(width - line.getEndPixel().getX() - 1, line.getEndPixel().getY(), line.getEndPixel().getColor()));
    }
}

void Plane::setPos(Pixel position)
{
    this->position = position;
}

void Plane::setPos(float x, float y)
{
    this->position = Pixel(x, y);
}

void Plane::setNLine(int nline) {
    this->nline = nline;
}

void Plane::setColor(int color) {
    this->col = color;
}

int Plane::getNLine() const {
    return nline;
}  

int Plane::getColor() const
{
    return col;
}

vector<Line> Plane::getLines() const
{
    return lines;
}

int Plane::getWidth() const
{
    return width;
}

int Plane::getHeight() const
{
    return height;
}

Pixel Plane::getPos() const
{
    return this->position;
}

const vector<Line> &Plane::getRefLines() const
{
    return lines;
}

const Pixel &Plane::getRefPos() const
{
    return this->position;
}