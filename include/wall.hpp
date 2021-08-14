#ifndef WALL_H
#define WALL_H
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
	};
}

#endif