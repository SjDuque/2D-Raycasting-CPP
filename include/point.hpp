#ifndef POINT_H
#define POINT_H

#include "math.h"

namespace raycast{
	class Point {
		public:
		float x, y;
		float dist(Point p);
	};
}

#endif