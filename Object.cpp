
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

        Plane *plane = new MoveablePlane(x, y, lines, planeColor, priority);
        this->planes.push_back(plane);
    }

    this->setHeight();
    this->setWidth();

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
    float xStart, xEnd;
    float xMin = 9999999; 
    float xMax = -9999999;

    for (Plane *plane: this->getPlanes())
    {
        for (Line line : plane->getLines())
        {
            xStart = line.getStartPixel().getX();
            xEnd = line.getEndPixel().getX();

            xMin = min(xMin, min(xStart, xEnd));
            xMax = max(xMax, max(xStart, xEnd));
        }
    }
    this->width = xMax - xMin + 1;
}

void Object::setHeight()
{
    float yStart, yEnd;
    float yMin = 9999999; 
    float yMax = -9999999;

    for (Plane *plane: this->getPlanes())
    {
        for (Line line : plane->getLines())
        {
            yStart = line.getStartPixel().getY();
            yEnd = line.getEndPixel().getY();

            yMin = min(yMin, min(yStart, yEnd));
            yMax = max(yMax, max(yStart, yEnd));
        }
    }
    this->height = yMax - yMin + 1;
}

vector<Plane *> Object::getPlanes() const
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

const vector<Plane *> &Object::getRefPlanes() const
{
    return this->planes;
}

const Pixel &Object::getRefPos() const
{
    return this->position;
}

void Object::reverseHorizontal()
{
    // implement reverse as an object
    for (Plane* plane : planes)
    {
        for (Line &line : plane->getLines())
        {
            line.setStartPixel(Pixel(width - line.getStartPixel().getX() - 1, line.getStartPixel().getY(), line.getStartPixel().getColor()));
            line.setEndPixel(Pixel(width - line.getEndPixel().getX() - 1, line.getEndPixel().getY(), line.getEndPixel().getColor()));
        }
    }
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