#include "ray.hpp"
#include "wall.hpp"
#include "point.hpp"
#include "math.h"

using namespace raycast;

//---------------------------------
// Constructor
//---------------------------------

Ray::Ray()
	: pos(new Point{0, 0}), angle(0) {}

Ray::Ray(Point* p, float angle)
	: pos(p), angle(0) {}

Ray::Ray(float x, float y, float angle)
	: pos(new Point{x, y}), angle(angle) {}

float Ray::getDirX()
{
	return cosf(this->angle);
}
float Ray::getDirY()
{
	return sinf(this->angle);
}

Point Ray::getDir()
{
	return Point{cosf(this->angle), sinf(this->angle)};
}

void Ray::pointTo(Point p)
{
	this->angle = atan2(p.y-this->pos->y, p.x-this->pos->x);
}

Point* Ray::cast(Wall wall)
{
	// shamelessly using algorithm from wikipedia
	// https://en.wikipedia.org/wiki/Line–line_intersection
	
	// the variables are the same ones from the wikipedia

	// coords for wall
	const float x1 = wall.a.x;
	const float y1 = wall.a.y;
	const float x2 = wall.b.x;
	const float y2 = wall.b.y;

	// coords for ray
	// x4, y4 are added from the direction of the ray to 
	// make a line segment projected from the ray
	const float x3 = this->pos->x;
	const float y3 = this->pos->y;
	const float x4 = x3 + cosf(this->angle);
	const float y4 = y3 + sinf(this->angle);
	
	// doing the math from "Given two points on each line segment"
	const float den = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
	const float t = ((x1-x3)*(y3-y4) - (y1-y3)*(x3-x4))/den;
	const float u = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3))/den;

	// if the denominator is 0 then the lines are parallel
	if (den == 0) return NULL;

	// 
	if (t >= 0 && t <= 1 && u >= 0)
	{
		return new Point{(x1 + t*(x2-x1)), (y1 + t*(y2-y1))};
	}

	return NULL;
}