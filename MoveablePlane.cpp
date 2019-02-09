
#include "MoveablePlane.hpp"

MoveablePlane::MoveablePlane(float x, float y, int nline, vector<Line> lines, int color, int priority) : Plane(x, y, nline, lines, color, priority)
{
    this->dx = 0;
    this->dy = 0;
    this->speed = 1;
}

MoveablePlane::MoveablePlane(float x, float y, float dx, float dy, float speed, int nline, vector<Line> lines, int color, int priority) : Plane(x, y, nline, lines, color, priority)
{
    float distance = sqrt(dx * dx + dy * dy);
    this->dx = 0;
    this->dy = 0;

    if (distance > 0)
    {
        this->dx = dx / distance;
        this->dy = dy / distance;
    }

    this->speed = speed;
}

MoveablePlane::MoveablePlane(const Plane &plane) : Plane(plane)
{
    this->dx = 0;
    this->dy = 0;
    this->speed = 1;
}

MoveablePlane::MoveablePlane(float dx, float dy, float speed, const Plane &plane) : Plane(plane)
{
    float distance = sqrt(dx * dx + dy * dy);
    this->dx = 0;
    this->dy = 0;

    if (distance > 0)
    {
        this->dx = dx / distance;
        this->dy = dy / distance;
    }

    this->speed = speed;
}

void MoveablePlane::setVector(float dx, float dy)
{
    float distance = sqrt(dx * dx + dy * dy);
    if (distance > 0)
    {
        this->dx = dx / distance;
        this->dy = dy / distance;
    }
}

void MoveablePlane::setSpeed(float speed)
{
    this->speed = speed;
}

float MoveablePlane::getDx() const
{
    return this->dx;
}

float MoveablePlane::getDy() const
{
    return this->dy;
}

float MoveablePlane::getSpeed() const
{
    return this->speed;
}

void MoveablePlane::move()
{
    this->position.setX(this->position.getX() + this->dx * this->speed);
    this->position.setY(this->position.getY() + this->dy * this->speed);
}

void MoveablePlane::selfRotation(float pivotX, float pivotY, float theta)
{
    float yMin, yMax, xMin, xMax;
    bool alreadyloop = false;

    pivotX -= this->position.getX();
    pivotY -= this->position.getY();

    for (Line &line : this->lines)
    {
        line.setStartPixel(line.getStartPixel().rotation(pivotX, pivotY, theta));
        line.setEndPixel(line.getEndPixel().rotation(pivotX, pivotY, theta));

        if (alreadyloop)
        {
            xMin = min(xMin, min(line.getStartPixel().getX(), line.getEndPixel().getX()));
            xMax = max(xMax, max(line.getStartPixel().getX(), line.getEndPixel().getX()));
            yMin = min(yMin, min(line.getStartPixel().getY(), line.getEndPixel().getY()));
            yMax = max(yMax, max(line.getStartPixel().getY(), line.getEndPixel().getY()));
        }
        else
        {
            xMin = min(line.getStartPixel().getX(), line.getEndPixel().getX());
            xMax = max(line.getStartPixel().getX(), line.getEndPixel().getX());
            yMin = min(line.getStartPixel().getY(), line.getEndPixel().getY());
            yMax = max(line.getStartPixel().getY(), line.getEndPixel().getY());
        }
        alreadyloop = true;
    }

    for (Line &line : this->lines)
    {
        line.setStartPixel(Pixel(line.getStartPixel().getX() - xMin, line.getStartPixel().getY() - yMin, line.getStartPixel().getColor()));
        line.setEndPixel(Pixel(line.getEndPixel().getX() - xMin, line.getEndPixel().getY() - yMin, line.getEndPixel().getColor()));
    }

    xMax -= xMin;
    yMax -= yMin;

    pivotX += this->position.getX();
    pivotY += this->position.getY();

    this->position.setPos(this->position.getX() + xMin, this->position.getY() + yMin);

    width = xMax + 1;
    height = yMax + 1;
}

void MoveablePlane::selfDilated(float pivotX, float pivotY, float scalingConstant)
{
    float yMin, yMax, xMin, xMax;
    bool alreadyloop = false;

    for (Line &line : this->lines)
    {
        line.setStartPixel(line.getStartPixel().dilated(pivotX, pivotY, scalingConstant));
        line.setEndPixel(line.getEndPixel().dilated(pivotX, pivotY, scalingConstant));

        if (alreadyloop)
        {
            xMin = min(xMin, min(line.getStartPixel().getX(), line.getEndPixel().getX()));
            xMax = max(xMax, max(line.getStartPixel().getX(), line.getEndPixel().getX()));
            yMin = min(yMin, min(line.getStartPixel().getY(), line.getEndPixel().getY()));
            yMax = max(yMax, max(line.getStartPixel().getY(), line.getEndPixel().getY()));
        }
        else
        {
            xMin = min(line.getStartPixel().getX(), line.getEndPixel().getX());
            xMax = max(line.getStartPixel().getX(), line.getEndPixel().getX());
            yMin = min(line.getStartPixel().getY(), line.getEndPixel().getY());
            yMax = max(line.getStartPixel().getY(), line.getEndPixel().getY());
        }
        alreadyloop = true;
    }

    for (Line &line : this->lines)
    {
        line.setStartPixel(Pixel(line.getStartPixel().getX() - xMin, line.getStartPixel().getY() - yMin, line.getStartPixel().getColor()));
        line.setEndPixel(Pixel(line.getEndPixel().getX() - xMin, line.getEndPixel().getY() - yMin, line.getEndPixel().getColor()));
    }

    xMax -= xMin;
    yMax -= yMin;

    this->position.setPos(this->position.getX() + xMin, this->position.getY() + yMin);

    width = xMax + 1;
    height = yMax + 1;
}
