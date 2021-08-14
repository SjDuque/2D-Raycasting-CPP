#ifndef RAY_H
#define RAY_H

#include "wall.hpp"

namespace raycast{
	class Ray 
	{
		private:
		Point* pos;
		float angle;

		public:
		// Constructors
		Ray();
		Ray(float x, float y, float angle);
		Ray(Point p, float angle);
		Ray(Point* p, float angle);

		// Getters and setters
		Point getPos();
		void setPos(Point* p);

		float getAngle();
		void setAngle(float a);

		float getDirX();
		float getDirY();
		Point getDir();

		// Methods
		void pointTo(Point p);
		Point* cast(Wall wall);
	};
}

#endif