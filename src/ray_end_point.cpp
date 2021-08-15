#include "ray_end_point.hpp"

using namespace raycast;

//---------------------------------
// Constructors
//---------------------------------

RayEndPoint::RayEndPoint(Ray* ray, EndPoint* endPoint)
	: ray(ray), endPoint(endPoint), dist(ray->getPos().dist(endPoint->getPos())) {}

