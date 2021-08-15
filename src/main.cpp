#include <iostream>
#include <vector>
#include <algorithm>    // std::sort

#include "ray.hpp"
#include "raylib.h"


const Color rayColor = RED;
const Color sightColor = WHITE;
const Color wallColor = GREEN;
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
	SetTargetFPS(targetFPS);

	// create vector of walls
	std::vector<raycast::Wall> walls;
	std::vector<raycast::Wall> square = raycast::Wall::createPolygon({
		raycast::Point{50, 50},
		raycast::Point{50,  100},
		raycast::Point{100,  100},
		raycast::Point{100,  50},
		});
	
	std::vector<raycast::Wall> triangle = raycast::Wall::createPolygon({
		raycast::Point{200, 70},
		raycast::Point{400,  200},
		raycast::Point{200,  300},
		});
	
	std::vector<raycast::Wall> trapezoid = raycast::Wall::createPolygon({
		raycast::Point{500, 200},
		raycast::Point{600,  200},
		raycast::Point{750, 400},
		raycast::Point{400,  400},
		});
	
	std::vector<raycast::Wall> barrier = raycast::Wall::createPolygon({
		raycast::Point{40, 40},
		raycast::Point{40, screenHeight-40},
		raycast::Point{screenWidth-40, screenHeight-40},
		raycast::Point{screenWidth-40,  40},
		});
	
	walls.insert(walls.end(), square.begin(), square.end());
	walls.insert(walls.end(), triangle.begin(), triangle.end());
	walls.insert(walls.end(), trapezoid.begin(), trapezoid.end());
	walls.insert(walls.end(), barrier.begin(), barrier.end());


	// Add all points to the points vector
	std::vector<raycast::Point> points;
	for (raycast::Wall wall : walls)
	{
		points.push_back(wall.getA());
		points.push_back(wall.getB());
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
	rays.reserve(points.size());

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

			for (auto wall : walls) 
			{
				raycast::Point* collision = ray.cast(wall);

				if (collision == NULL)
					continue;

				float dist = collision->dist(ray.getPos());
				// float dist = ray.cast(wall, lengthRay);

				if(dist < closestDist) 
					closestDist = dist;
			}
			collisions.push_back(raycast::Point{ray.getPos().x + ray.getDirX()*closestDist, ray.getPos().y + ray.getDirY()*closestDist});
		}

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
			ClearBackground(BLACK);

			// Draw Walls
			if (drawWalls) {
				for (auto wall : walls)
				{
					DrawLineEx(Vector2{wall.getA().x, wall.getA().y}, Vector2{wall.getB().x, wall.getB().y}, 2, wallColor);
				}	
			}

			Vector2 center{rays[0].getPos().x, rays[0].getPos().y};
			for (int i = 0; i < collisions.size(); i++)
			{
				// Draw the triangles made from the collision points in counterclockwise order
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