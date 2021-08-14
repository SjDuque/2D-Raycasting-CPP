#ifndef WALL_H
#define WALL_H
#include "point.hpp"

namespace raycast{
	class Wall 
	{
		public:
		Wall(float x1, float y1, float x2, float y2);
		Point a;
		Point b;
	};
}

#endif