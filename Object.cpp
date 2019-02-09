
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

    int nline;
    int priority;
    int xStart, yStart, xEnd, yEnd;
    int xMin, xMax, yMin, yMax;
    int colorPlane;
    unsigned int colorStart, colorEnd;

    inFile >> nplane;
    for (int i = 0; i < nplane; ++i)
    {
        inFile >> nline;
        inFile >> hex >> colorPlane;
        inFile >> priority;
        vector<Line> lines;
        for (int j = 0; j < nline; ++j) {
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
        Plane plane = Plane(x, y, nline, lines, colorPlane, priority);
        planes.push_back(plane);
    }
    inFile.close();
}

void Object::setPos(Pixel position)
{
    this->position = position;
}

void Object::setPos(float x, float y)
{
    this->position = Pixel(x, y);
}

void Object::setNPlane(int nplane)
{
    this->nplane = nplane;
}

vector<Plane> Object::getPlanes() const
{
    return planes;
}

Pixel Object::getPos() const
{
    return this->position;
}

int Object::getNPlane() const
{
    return this->nplane;
}

const vector<Plane> &Object::getRefPlanes() const
{
    return planes;
}

const Pixel &Object::getRefPos() const
{
    return this->position;
}