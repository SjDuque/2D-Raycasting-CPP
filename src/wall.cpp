#include "wall.hpp"
#include "point.hpp"
//---------------------------------
// Constructor
//---------------------------------

raycast::Wall::Wall(float x1, float y1, float x2, float y2)
	: a(Point{x1, y1}), b(Point{x2, y2}) {}

