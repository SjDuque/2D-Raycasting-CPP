#ifndef RAY_END_POINT_H
#define RAY_END_POINT_H

#include "ray.hpp"

namespace raycast{
	class RayEndPoint{
		public:
		EndPoint* endPoint;
		Ray* ray;
		float dist;
		RayEndPoint(Ray* ray, EndPoint* endPoint);
	};
}

#endif