#ifndef RAY_H
#define RAY_H

#include "end_point.hpp"

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
		float getX();
		float getY();
		Point getPos();
		Point* getPosPtr();
		void setPos(Point* p);

		float getAngle();
		void setAngle(float a);

		float getDirX();
		float getDirY();
		Point getDir();

		// Methods
		float angleTo(Point p);
		void pointTo(Point p);
		Point* cast(EndPoint endPoint);
		float cast(EndPoint endPoint, const float maxDist);

		// Operator overloading
		friend bool operator<(const Ray& r1, const Ray& r2) { return r1.angle < r2.angle; }
	};
}

#endif