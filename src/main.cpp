#include <iostream>
#include <vector>
#include <algorithm>    // std::sort

#include "ray.hpp"
#include "raylib.h"


const Color rayColor = RED;
const Color sightColor = WHITE;
const Color endPointColor = GREEN;
const Color playerColor = BLUE;
const Color background = BLACK;
const int screenWidth = 800;
const int screenHeight = 450;
const int targetFPS = 60;
const float lengthRay = 1000;
const float theta = 0.001; // angle between "subrays"

bool drawWalls = true;
bool drawShadows = true;
bool drawRays = true;
bool drawPlayer = true;

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	InitWindow(screenWidth, screenHeight, "2D Raycasting");
	// SetTargetFPS(targetFPS);

	// create vector of endPoints
	std::vector<raycast::EndPoint> endPoints;
	std::vector<raycast::EndPoint> square = raycast::EndPoint::createPolygon({
		raycast::Point{50, 50},
		raycast::Point{50,  100},
		raycast::Point{100,  100},
		raycast::Point{100,  50},
		});
	
	std::vector<raycast::EndPoint> triangle = raycast::EndPoint::createPolygon({
		raycast::Point{200, 70},
		raycast::Point{400,  200},
		raycast::Point{200,  300},
		});
	
	std::vector<raycast::EndPoint> trapezoid = raycast::EndPoint::createPolygon({
		raycast::Point{500, 200},
		raycast::Point{600,  200},
		raycast::Point{750, 350},
		raycast::Point{400,  350},
		});
	
	std::vector<raycast::EndPoint> barrier = raycast::EndPoint::createPolygon({
		raycast::Point{40, 40},
		raycast::Point{40, screenHeight-40},
		raycast::Point{screenWidth-40, screenHeight-40},
		raycast::Point{screenWidth-40,  40},
		});

	std::vector<raycast::EndPoint> circle = raycast::EndPoint::createCircle(
		raycast::Point{150, 350}, 50, 100
		);
	
	endPoints.insert(endPoints.end(), square.begin(), square.end());
	endPoints.insert(endPoints.end(), triangle.begin(), triangle.end());
	endPoints.insert(endPoints.end(), trapezoid.begin(), trapezoid.end());
	endPoints.insert(endPoints.end(), barrier.begin(), barrier.end());
	endPoints.insert(endPoints.end(), circle.begin(), circle.end());

	// // Remove duplicates from the point vector
	// for (int i = 0; i < endPoints.size(); i++)
	// {
	// 	for (int j = i+1; j < endPoints.size(); j++)
	// 	{
	// 		if (endPoints[i].getX() == endPoints[j].getX() && endPoints[i].getY() == endPoints[j].getY())
	// 			endPoints.erase(endPoints.begin() + j);
	// 	}
	// }

	// Create vector of rays with the same point
	// angle will be set later in the game loop
	raycast::Point ray_point{10, screenHeight/2}; // shared point for rays
	std::vector<raycast::RayEndPoint> rayEndPoints;
	rayEndPoints.reserve(endPoints.size()*2);

	// Store all the points of collision
	std::vector<raycast::Point> collisions;
	collisions.reserve(rayEndPoints.size());

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------
		
		// Have rays follow the mouse
		ray_point.x = GetMouseX();
		ray_point.y = GetMouseY();


		rayEndPoints.clear();
		// Set rays to follow points
		for (int i = 0; i < endPoints.size(); i++)
		{	
			auto ray1 = new raycast::Ray{ray_point, 0};
			auto ray2 = new raycast::Ray{ray_point, 0};
			ray1->pointTo(endPoints[i].getPos());
			ray2->pointTo(endPoints[i].getOtherPos());
			rayEndPoints.push_back(raycast::RayEndPoint{ray1, &endPoints[i]});
			rayEndPoints.push_back(raycast::RayEndPoint{ray2, endPoints[i].getOtherPtr()});
		}
		// Sort rays based on their angles
		std::sort(rayEndPoints.begin(), rayEndPoints.end());

		for (int i = 0; i < rayEndPoints.size(); i++)
		{	
			auto rayEndPoint = rayEndPoints[i];

			auto ray = *rayEndPoint.ray;
			auto endPoint = rayEndPoint.endPoint->getOther();
			float a = ray.angleTo(endPoint.getPos());
			float dist = endPoint.getPos().dist(ray_point);

			if (dist < rayEndPoint.dist)
				dist = rayEndPoint.dist;

			if (a>ray.getAngle())
			{
				int j;
				for (j = i + 1; j < rayEndPoints.size(); j++){
					auto otherRayEndPoint = rayEndPoints[j];
					if (otherRayEndPoint.dist < dist || a < otherRayEndPoint.ray->getAngle())
						break;
				}
				if (j != i+1)
					rayEndPoints.erase(rayEndPoints.begin()+(i+1), rayEndPoints.begin()+j-1);
			}
		}

		// Empty collisions vector to be used in for loop
		collisions.clear();

		// Find all the points of collision for the rays
		for (auto rayEndPoint : rayEndPoints)
		{	
			// Sets the ray as a line segment of size lengthRay 
			float closestDist = lengthRay;
			auto ray = *rayEndPoint.ray;

			for (auto endPoint : endPoints) 
			{
				// raycast::Point* collision = ray.cast(endPoint);

				// if (collision == NULL)
				// 	continue;

				// float dist = collision->dist(ray.getPos());
				float dist = ray.cast(endPoint, lengthRay);

				if(dist < closestDist) 
					closestDist = dist;
			}
			collisions.push_back(raycast::Point{ray.getX() + ray.getDirX()*closestDist, ray.getY() + ray.getDirY()*closestDist});
		}

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
			ClearBackground(BLACK);

			// Draw EndPoints
			if (drawWalls) {
				for (auto endPoint : endPoints)
				{
					DrawLineEx(Vector2{endPoint.getX(), endPoint.getY()}, Vector2{endPoint.getOtherX(), endPoint.getOtherY()}, 2, endPointColor);
				}	
			}

			Vector2 center{ray_point.x, ray_point.y};
			for (int i = 0; i < collisions.size(); i++)
			{
				// Draw the triangles made from the collision points
				if (drawShadows)
				{
					Vector2 p1{collisions[i].x, collisions[i].y};
					Vector2 p2{collisions[(i+1)%collisions.size()].x, collisions[(i+1)%collisions.size()].y};
					DrawTriangle(p1, center, p2, sightColor);
				}
				// Draw the rays as a line segment between the start and point of collision
				if (drawRays)
				{
					Vector2 end_ray{collisions[i].x, collisions[i].y};
					DrawLineEx(center, end_ray, 2, rayColor);
				}
			}
			
			if (drawPlayer) 
				DrawCircleV(center, 4, playerColor);


			DrawFPS(10, 10);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------

	CloseWindow();                // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}