#ifndef RAY_H
#define RAY_H

#include "wall.hpp"
#include "point.hpp"

namespace raycast{
	class Ray 
	{
		public:

		// Properties
		Point* pos;
		float angle;

		// Constructors
		Ray();
		Ray(Point* p, float angle);
		Ray(float x, float y, float angle);

		// Methods
		float getDirX();
		float getDirY();
		Point getDir();
		void pointTo(Point p);
		Point* cast(Wall wall);
	};
}

#endif