#include "point.hpp"
#include "math.h"

using namespace raycast;

float Point::dist(Point p){
    float a = p.x - this->x;
    float b = p.y - this->y;
    return sqrtf(a*a + b*b);
}