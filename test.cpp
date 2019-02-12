#include <iostream>
#include "Master.hpp"
#include "MoveableObject.hpp"
#include "Object.hpp"

using namespace std;

class Runner : public Master
{
protected:
    Object test;
  public:
    Runner(int h = 700, int w = 1000) : Master(h, w) {
        test = Object(0, 0, "Asset/object_wheel.txt");
    }
    void start(){
        clearWindow();
        drawObject(test);
        drawSolidObject(test);
        flush();
    }
};

int main()
{
    Runner run;
    run.start();
    return 0;
}