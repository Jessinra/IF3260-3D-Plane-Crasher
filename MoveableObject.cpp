
#include "MoveableObject.hpp"

MoveableObject::MoveableObject(float x, float y, const std::string &filename) : Object(x, y, filename)
{
    this->dx = 0;
    this->dy = 0;
    this->speed = 1;
}

MoveableObject::MoveableObject(float x, float y, float dx, float dy, float speed, const std::string &filename) : Object(x, y, filename)
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

MoveableObject::MoveableObject(const Object &obj) : Object(obj)
{
    this->dx = 0;
    this->dy = 0;
    this->speed = 1;
}

MoveableObject::MoveableObject(float dx, float dy, float speed, const Object &obj) : Object(obj)
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

void MoveableObject::setVector(float dx, float dy)
{
    float distance = sqrt(dx * dx + dy * dy);
    if (distance > 0)
    {
        this->dx = dx / distance;
        this->dy = dy / distance;
    }
}

void MoveableObject::setSpeed(float speed)
{
    this->speed = speed;
}

float MoveableObject::getDx() const
{
    return this->dx;
}

float MoveableObject::getDy() const
{
    return this->dy;
}

float MoveableObject::getSpeed() const
{
    return this->speed;
}

void MoveableObject::move()
{
    for (Plane *plane : this->planes)
    {
        plane->move();
    }
}

void MoveableObject::selfRotation(float pivotX, float pivotY, float theta)
{
    for (Plane *plane : this->planes)
    {
        plane->selfRotation(pivotX, pivotY, theta);
    }
}

void MoveableObject::selfDilated(float pivotX, float pivotY, float scalingConstant)
{
    for (Plane *plane : this->planes)
    {
        plane->selfDilated(pivotX, pivotY, scalingConstant);
    }
}

