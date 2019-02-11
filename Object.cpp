
#include "Object.hpp"

Object::Object()
{
}

Object::Object(float x, float y, std::string filename)
{
    setPos(x, y);

    // initialize lines
    ifstream inFile;
    inFile.open(filename);

    if (!inFile)
    {
        cout << "\nError opening file.\n";
        exit(1);
    }

    int nLine;
    int priority;
    int xStart, yStart, xEnd, yEnd;
    int planeColor;
    unsigned int colorStart, colorEnd;

    inFile >> nPlane;
    for (int i = 0; i < nPlane; ++i)
    {
        inFile >> nLine;
        inFile >> hex >> planeColor;
        inFile >> priority;

        vector<Line> lines;
        for (int j = 0; j < nLine; ++j)
        {

            inFile >> dec >> xStart;
            inFile >> yStart;
            inFile >> hex >> colorStart;
            inFile >> dec >> xEnd;
            inFile >> yEnd;
            inFile >> hex >> colorEnd;

            Pixel startpx = Pixel(xStart, yStart, colorStart);
            Pixel endpx = Pixel(xEnd, yEnd, colorEnd);
            Line line = Line(startpx, endpx);
            lines.push_back(line);
        }

        this->planes.emplace_back(MoveablePlane(x, y, lines, planeColor, priority));
    }

    calculate();

    inFile.close();
}

void Object::setPos(Point position)
{
    this->position = position;
}

void Object::setPos(float x, float y)
{
    this->position = Point(x, y);
}

void Object::setNPlane(int nPlane)
{
    this->nPlane = nPlane;
}

vector<MoveablePlane> Object::getPlanes() const
{
    return this->planes;
}

Point Object::getPos() const
{
    return this->position;
}

int Object::getNPlane() const
{
    return this->nPlane;
}

int Object::getWidth() const
{
    return this->width;
}
int Object::getHeight() const
{
    return this->height;
}

vector<MoveablePlane> &Object::getRefPlanes(){
    return this->planes;
}

const Point &Object::getRefPos() const
{
    return this->position;
}

void Object::reverseHorizontal()
{
    // implement reverse as an object
    for (Plane &plane : planes)
    {
        for (Line &line : plane.getRefLines())
        {
            line.setStartPixel(Pixel(width - line.getStartPixel().getX() - 1, line.getStartPixel().getY(), line.getStartPixel().getColor()));
            line.setEndPixel(Pixel(width - line.getEndPixel().getX() - 1, line.getEndPixel().getY(), line.getEndPixel().getColor()));
        }
    }
}

bool Object::outOfWindow(int height, int width) const
{
    return position.getX() + xMax < 0 || position.getY() + yMax < 0 || position.getX() >= width || position.getY() >= height;
}

const vector<MoveablePlane> &Object::getConstRefPlanes() const {
    return this->planes;
}

void Object::calculate() {
    if(planes.empty()) return;

    xMin = planes[0].getUpperLeft().getX() + planes[0].getRefPos().getX();
    yMin = planes[0].getUpperLeft().getY() + planes[0].getRefPos().getY();
    xMax = planes[0].getLowerRight().getX() + planes[0].getRefPos().getX();
    yMax = planes[0].getLowerRight().getY() + planes[0].getRefPos().getY();

    for(int i=1;i<planes.size();++i){
        xMin = min(xMin, planes[0].getUpperLeft().getX() + planes[0].getRefPos().getX());
        yMin = min(yMin, planes[0].getUpperLeft().getY() + planes[0].getRefPos().getY());
        xMax = max(xMax, planes[0].getLowerRight().getX() + planes[0].getRefPos().getX());
        yMax = max(yMax, planes[0].getLowerRight().getY() + planes[0].getRefPos().getY());
    }
}
