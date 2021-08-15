#include "ray.hpp"
#include "math.h"

using namespace raycast;

//---------------------------------
// Constructors
//---------------------------------

Ray::Ray()
	: pos(new Point{0, 0}), angle(0) {}

Ray::Ray(Point p, float angle)
	: pos(new Point{p.x, p.y}), angle(angle) {}

Ray::Ray(Point* p, float angle)
	: pos(p), angle(angle) {}

Ray::Ray(float x, float y, float angle)
	: pos(new Point{x, y}), angle(angle) {}

//---------------------------------
// Getters and setters
//---------------------------------

Point Ray::getPos(){
	return *this->pos;
}
void Ray::setPos(Point* p){
	this->pos = p;
}

float Ray::getAngle(){
	return this->angle;
}
void Ray::setAngle(float a){
	this->angle = a;
}

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

void setPos(Point* p);
float getDirX();
float getDirY();
Point getDir();

void Ray::pointTo(Point p)
{
	this->angle = atan2(p.y-this->pos->y, p.x-this->pos->x);
}

//---------------------------------
// Methods
//---------------------------------

Point* Ray::cast(Wall wall)
{
	// shamelessly using algorithm from wikipedia
	// https://en.wikipedia.org/wiki/Line–line_intersection
	
	// the variables are the same ones from the wikipedia

	// coords for wall
	const float x1 = wall.getA().x;
	const float y1 = wall.getA().y;
	const float x2 = wall.getB().x;
	const float y2 = wall.getB().y;

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

float Ray::cast(Wall wall, float maxDist)
{
	const float a = -this->angle;
	const float x1 = wall.getA().x - this->getPos().x;
	const float y1 = wall.getA().y - this->getPos().y;
	const float x2 = wall.getB().x - this->getPos().x;
	const float y2 = wall.getB().y - this->getPos().y;

	float segX1p = cos(a)*x1 + -sin(a)*y1;/*Matrix rotation of point 1*/
    float segY1p = sin(a)*x1 +  cos(a)*y1;
    float segX2p = cos(a)*x2 + -sin(a)*y2;/*Matrix rotation of point 2*/
    float segY2p = sin(a)*x2 +  cos(a)*y2;
	

	if (segY1p*segY2p > 0) return maxDist;

	float dist = -(segY1p * (segX1p-segX2p)/
				  (segY1p-segY2p) - segX1p);
	
	if (dist < 0 || isinf(dist)) return maxDist;

    return dist;
}