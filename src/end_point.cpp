#include "end_point.hpp"
#include "math.h"

using namespace raycast;

// Constructors
EndPoint::EndPoint(float x1, float y1, float x2, float y2)
	: EndPoint(Point{x1, y1}, Point{x2, y2}) {}

EndPoint::EndPoint(Point start, Point end)
	: pos(new Point{start.x, start.y}), other(new EndPoint{end, this}) {}

EndPoint::EndPoint(Point start, EndPoint* end)
	: pos(new Point{start.x, start.y}), other(end) {}

// Get Methods
EndPoint EndPoint::getOther()
{
	return *this->other;
}
EndPoint* EndPoint::getOtherPtr()
{
	return this->other;
}

float EndPoint::getX()
{
	return this->pos->x;
}
float EndPoint::getY()
{
	return this->pos->y;
}
Point EndPoint::getPos()
{
	return *this->pos;
}

float EndPoint::getOtherX()
{
	return this->other->getX();
}
float EndPoint::getOtherY()
{
	return this->other->getY();
}
Point EndPoint::getOtherPos()
{
	return this->other->getPos();
}

// Create Shapes

std::vector<EndPoint> EndPoint::createPolygon(std::vector<Point> points)
{
	std::vector<EndPoint> sides;
	sides.reserve(points.size());

	for (int i = 0; i < points.size(); i++)
	{
		sides.push_back(EndPoint{points[i], points[(i+1)%points.size()]});
	}

	return sides;
}
std::vector<EndPoint> EndPoint::createCircle(Point center, const int radius, const int numSides)
{
	std::vector<Point> circlePoints;
	circlePoints.reserve(numSides);
	for (int i = 0; i < numSides; i++)
	{
		float a = 2*M_PI/numSides*i;
		float x = center.x + radius * cos(a);
		float y = center.y + radius * sin(a);
		circlePoints.push_back(raycast::Point{x, y});
	}

	std::vector<EndPoint> sides;
	sides.reserve(numSides);

	for (int i = 0; i < numSides; i++)
	{
		sides.push_back(EndPoint{circlePoints[i], circlePoints[(i+1)%numSides]});
	}

	return sides;
}