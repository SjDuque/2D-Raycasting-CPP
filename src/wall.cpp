#include "wall.hpp"
#include "point.hpp"

using namespace raycast;
//---------------------------------
// Constructor
//---------------------------------

Wall::Wall(float x1, float y1, float x2, float y2)
	: a(new Point{x1, y1}), b(new Point{x2, y2}) {}

Wall::Wall(Point a, Point b)
	: a(&a), b(&a) {}

Wall::Wall(Point* a, Point* b)
	: a(a), b(a) {}

Point Wall::getA()
{
	return *this->a;
}

Point Wall::getB()
{
	return *this->b;
}