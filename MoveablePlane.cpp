
#include "MoveablePlane.hpp"

MoveablePlane::MoveablePlane(float x, float y, const vector<Line> &lines, int color, int priority) : Plane(lines, color, priority)
{
    this->position = Pixel(x, y);
}

MoveablePlane::MoveablePlane(float x, float y, const Plane &plane) : Plane(plane)
{
    this->position = Pixel(x, y);
}

void MoveablePlane::setPos(Pixel position)
{
    this->position = position;
}

void MoveablePlane::setPos(float x, float y)
{
    this->position = Pixel(x, y);
}

void MoveablePlane::calculate(){
    if(lines.empty()) return;

    this->xMin = min(lines[0].getRefStartPixel().getX(), lines[0].getRefEndPixel().getX());
    this->xMax = max(lines[0].getRefStartPixel().getX(), lines[0].getRefEndPixel().getX());
    this->yMin = min(lines[0].getRefStartPixel().getY(), lines[0].getRefEndPixel().getY());
    this->yMax = max(lines[0].getRefStartPixel().getY(), lines[0].getRefEndPixel().getY());
    for(int i=1;i<lines.size();++i){
        this->xMin = min(this->xMin, min(lines[i].getRefStartPixel().getX(), lines[i].getRefEndPixel().getX()));
        this->xMax = max(this->xMax, max(lines[i].getRefStartPixel().getX(), lines[i].getRefEndPixel().getX()));
        this->yMin = min(this->yMin, min(lines[i].getRefStartPixel().getY(), lines[i].getRefEndPixel().getY()));
        this->yMax = max(this->xMax, max(lines[i].getRefStartPixel().getY(), lines[i].getRefEndPixel().getY()));
    }

    for (Line &line : this->lines){
        line.setStartPixel(Pixel(line.getStartPixel().getX() - this->xMin, line.getStartPixel().getY() - this->yMin, line.getStartPixel().getColor()));
        line.setEndPixel(Pixel(line.getEndPixel().getX() - this->xMin, line.getEndPixel().getY() - this->yMin, line.getEndPixel().getColor()));
    }

    this->xMax -= this->xMin;
    this->yMax -= this->yMin;

    this->position.setPos(this->position.getX() + xMin, this->position.getY() + yMin);

    this->xMin = this->yMin = 0;
}

void MoveablePlane::selfRotation(float pivotX, float pivotY, float theta)
{
    pivotX -= this->position.getX();
    pivotY -= this->position.getY();

    for (Line &line : this->lines)
    {
        line.setStartPixel(line.getStartPixel().rotation(pivotX, pivotY, theta));
        line.setEndPixel(line.getEndPixel().rotation(pivotX, pivotY, theta));
    }

    calculate();
}

void MoveablePlane::selfDilated(float pivotX, float pivotY, float scalingConstant)
{
    for (Line &line : this->lines){
        line.setStartPixel(line.getStartPixel().dilated(pivotX, pivotY, scalingConstant));
        line.setEndPixel(line.getEndPixel().dilated(pivotX, pivotY, scalingConstant));
    }

    calculate();
}

Pixel MoveablePlane::getPos() const {
    return this->position;
}

const Pixel &MoveablePlane::getRefPos() const {
    return this->position;
}
