#include "Pixel.hpp"
#include <cmath>
#include <iostream>
#include "Color.hpp"

Pixel::Pixel()
{
    this->x = 0;
    this->y = 0;
    this->color = Color::BLACK;
}

Pixel::Pixel(float x, float y)
{
    this->x = x;
    this->y = y;
    this->color = Color::WHITE;
}

Pixel::Pixel(float x, float y, unsigned int color)
{
    this->x = x;
    this->y = y;
    this->color = color;
}

float Pixel::getX() const
{
    return this->x;
}

float Pixel::getY() const
{
    return this->y;
}

unsigned int Pixel::getColor() const
{
    return this->color;
}

void Pixel::setX(float x)
{
    this->x = x;
}

void Pixel::setY(float y)
{
    this->y = y;
}

void Pixel::setPos(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Pixel::setColor(unsigned int color)
{
    this->color = color;
}

Pixel Pixel::rotation(float pivotX, float pivotY, float theta)
{
    int resultX = this->x;
    int resultY = this->y;

    resultX -= pivotX;
    resultY -= pivotY;

    float sinTheta = sin(theta * PI / 180);
    float cosTheta = cos(theta * PI / 180);

    float xnew = resultX * cosTheta - resultY * sinTheta;
    float ynew = resultX * sinTheta + resultY * cosTheta;

    resultX = xnew + pivotX;
    resultY = ynew + pivotY;

    return Pixel(resultX, resultY, this->color);
}

Pixel Pixel::dilated(float pivotX, float pivotY, float scalingConstant)
{
    int resultX = scalingConstant * (x - pivotX) + pivotX;
    int resultY = scalingConstant * (y - pivotY) + pivotY;

    return Pixel(resultX, resultY, this->color);
}