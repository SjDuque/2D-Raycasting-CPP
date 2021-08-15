#ifndef END_POINT_H
#define END_POINT_H

#include "point.hpp"
#include <vector>

namespace raycast{
	class EndPoint {
		private:
		Point* pos;
		EndPoint* other;

		public:
		EndPoint(float x1, float y1, float x2, float y2);
		EndPoint(Point start, Point end);
		EndPoint(Point start, EndPoint* end);

		// Getters setters
		EndPoint getOther();
		EndPoint* getOtherPtr();
		float getX();
		float getY();
		Point getPos();
		float getOtherX();
		float getOtherY();
		Point getOtherPos();

		// Create shapes
		static std::vector<EndPoint> createPolygon(std::vector<Point> points);
		static std::vector<EndPoint> createCircle(Point center, const int radius, const int numSides);
	};
}

#endif