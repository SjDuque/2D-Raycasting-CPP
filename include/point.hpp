#ifndef POINT_H
#define POINT_H

namespace raycast{
	class Point {
		public:
		float x, y;
		float dist(Point p);

		friend bool operator==(const Point& p1, const Point& p2) { return p1.x == p2.x && p1.y == p2.y; }
	};
	
}

#endif