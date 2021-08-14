#ifndef POINT_H
#define POINT_H

namespace raycast{
	class Point {
		public:
		float x, y;
		float dist(Point p);
	};
}

#endif