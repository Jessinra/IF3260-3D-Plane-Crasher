
#include "Plane.hpp"

Plane::Plane()
{
}

Plane::Plane(float x, float y, vector<Line> lines, int color, int priority)
{
    this->setPos(x, y);
    this->lines = lines;
    this->color = color;
    this->priority = priority;

    this->setHeight();
    this->setWidth();
}

bool Plane::outOfWindow(int height, int width) const
{
    return (this->position.getX() >= width || this->position.getY() >= height || this->position.getX() <= -width || this->position.getY() <= -height);
}

void Plane::reverseHorizontal()
{
    for (Line &line : lines)
    {
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

void Plane::setColor(int color)
{
    this->color = color;
}

void Plane::setPriority(int priority)
{
    this->priority = priority;
}

void Plane::setWidth()
{
    float xStart, xEnd;
    float xMin = 9999999; 
    float xMax = -9999999;

    for (Line line : this->lines)
    {
        xStart = line.getStartPixel().getX();
        xEnd = line.getEndPixel().getX();

        xMin = min(xMin, min(xStart, xEnd));
        xMax = max(xMax, max(xStart, xEnd));
    }

    this->width = xMax - xMin + 1;
}

void Plane::setHeight()
{
    float yStart, yEnd;
    float yMin = 9999999; 
    float yMax = -9999999;

    for (Line line : this->lines)
    {
        yStart = line.getStartPixel().getY();
        yEnd = line.getEndPixel().getY();

        yMin = min(yMin, min(yStart, yEnd));
        yMax = max(yMax, max(yStart, yEnd));
    }

    this->height = yMax - yMin + 1;
}

int Plane::getColor() const
{
    return this->color;
}

int Plane::getPriority() const
{
    return this->priority;
}

int Plane::getWidth() const
{
    return this->width;
}

int Plane::getHeight() const
{
    return this->height;
}

vector<Line> Plane::getLines() const
{
    return this->lines;
}

Pixel Plane::getPos() const
{
    return this->position;
}

const vector<Line> &Plane::getRefLines() const
{
    return this->lines;
}

const Pixel &Plane::getRefPos() const
{
    return this->position;
}

void Plane::move()
{
    // Polymorphism
}

void Plane::selfRotation(float pivotX, float pivotY, float theta)
{
    // Polymorphism
}

void Plane::selfDilated(float pivotX, float pivotY, float scalingConstant)
{
    // Polymorphism
}
