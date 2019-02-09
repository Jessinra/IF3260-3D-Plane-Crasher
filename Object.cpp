
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

        Plane *plane = new MoveablePlane(x, y, nLine, lines, planeColor, priority);
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

void Object::setNPlane(int nPlane)
{
    this->nPlane = nPlane;
}

void Object::setWidth()
{
    // TODO : calculate total width of object
}

void Object::setHeight()
{
    // TODO : calculate total height of object
}

vector<Plane*> Object::getPlanes() const
{
    return this->planes;
}

Pixel Object::getPos() const
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

const vector<Plane*> &Object::getRefPlanes() const
{
    return this->planes;
}

const Pixel &Object::getRefPos() const
{
    return this->position;
}

void Object::reverseHorizontal()
{
    // TODO : implement reverse as an object
}

bool Object::outOfWindow(int height, int width) const
{
    for (const Plane *plane : this->getRefPlanes())
    {
        if (plane->outOfWindow(height, width))
        {
            return true;
        }
    }

    return false;
}