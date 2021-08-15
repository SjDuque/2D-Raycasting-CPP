#ifndef WALL_H
#define WALL_H

#include <vector>

#include "point.hpp"

namespace raycast{
	class Wall 
	{
		private:
		Point* a;
		Point* b;
		
		public:
		Wall(float x1, float y1, float x2, float y2);
		Wall(Point a, Point b);
		Wall(Point* a, Point* b);
		
		Point getA();
		Point getB();

		static std::vector<Wall> createPolygon(std::vector<Point> points);
		static std::vector<Wall> createCircle(Point center, int radius, int sides);
	};
}

#endif