#include "wall.hpp"

using namespace raycast;

//---------------------------------
// Constructor
//---------------------------------

Wall::Wall(float x1, float y1, float x2, float y2)
	: a(new Point{x1, y1}), b(new Point{x2, y2}) {}

Wall::Wall(Point a, Point b)
	: Wall(a.x, a.y, b.x, b.y) {}

Wall::Wall(Point* a, Point* b)
	: a(a), b(a) {}

//---------------------------------
// Getters and setters
//---------------------------------

Point Wall::getA()
{
	return *this->a;
}
Point Wall::getB()
{
	return *this->b;
}

//---------------------------------
// Methods
//---------------------------------
std::vector<Wall> Wall::createPolygon(std::vector<Point> points)
{
	std::vector<Wall> sides;
	sides.reserve(points.size());

	for (int i = 0; i < points.size(); i++)
	{
		sides.push_back(Wall{points[i], points[(i+1)%points.size()]});
	}

	return sides;
}