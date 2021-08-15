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

bool drawEndPoints = false;
bool drawShadows = true;
bool drawRays = false;
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

	// Add all points to the points vector
	std::vector<raycast::Point> points;
	for (raycast::EndPoint endPoint : endPoints)
	{
		points.push_back(endPoint.getPos());
		points.push_back(endPoint.getOtherPos());
	}

	// Remove duplicates from the point vector
	for (int i = 0; i < points.size(); i++)
	{
		for (int j = i+1; j < points.size(); j++)
		{
			if (points[i].x == points[j].x && points[i].y == points[j].y)
				points.erase(points.begin() + j);
		}
	}

	// Create vector of rays with the same point
	// angle will be set later in the game loop
	raycast::Point ray_point{10, screenHeight/2}; // shared point for rays
	std::vector<raycast::Ray> rays;
	rays.reserve(points.size()*3);

	for (int a = 0; a < points.size()*3; a++)
		rays.push_back(raycast::Ray{&ray_point, 0});

	// Store all the points of collision
	std::vector<raycast::Point> collisions;
	collisions.reserve(rays.size());

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

		// Set rays to follow points
		for (int a = 0; a < points.size()*3; a+=3)
		{
			rays[a].pointTo(points[a/3]);
			rays[a+1].setAngle(rays[a].getAngle()+theta);
			rays[a+2].setAngle(rays[a].getAngle()-theta);
		}
		// Sort rays based on their angles
		std::sort(rays.begin(), rays.end());

		// Empty collisions vector to be used in for loop
		collisions.clear();

		// Find all the points of collision for the rays
		for (auto ray : rays)
		{	
			// Sets the ray as a line segment of size lengthRay 
			float closestDist = lengthRay;

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
			if (drawEndPoints) {
				for (auto endPoint : endPoints)
				{
					DrawLineEx(Vector2{endPoint.getX(), endPoint.getY()}, Vector2{endPoint.getOtherX(), endPoint.getOtherY()}, 2, endPointColor);
				}	
			}

			Vector2 center{rays[0].getPos().x, rays[0].getPos().y};
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