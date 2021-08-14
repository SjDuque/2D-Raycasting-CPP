#include <iostream>
#include <vector>

#include "ray.hpp"
#include "wall.hpp"
#include "raylib.h"

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;
	const int targetFPS = 60;
	InitWindow(screenWidth, screenHeight, "2D Raycasting");
	SetTargetFPS(targetFPS);


	// create vector of walls
	std::vector<raycast::Wall> walls;
	walls.push_back(raycast::Wall{screenWidth-10, 10, screenWidth-20, screenHeight-100});
	walls.push_back(raycast::Wall{screenWidth-20, screenHeight-100, 100, screenHeight-10});
	walls.push_back(raycast::Wall{100, screenHeight-10, screenWidth-10, 10});

	// create vector of rays
	const int num_rays = 100;
	std::vector<raycast::Ray> rays;
	raycast::Point ray_point{10, screenHeight/2};

	for (int a = 0; a < num_rays; a++)
	{
		rays.push_back(raycast::Ray{&ray_point, 2*PI/num_rays*a});
	}
	// 
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------
		if (IsKeyDown(KEY_UP))
		{
			ray_point.y -= 60*GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			ray_point.y += 60*GetFrameTime();
		}

		if (IsKeyDown(KEY_LEFT))
		{
			ray_point.x -= 60*GetFrameTime();
		}
		if (IsKeyDown(KEY_RIGHT))
		{
			ray_point.x += 60*GetFrameTime();
		}
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

			ClearBackground(BLACK);

			// Draw Walls
			for (raycast::Wall wall : walls)
			{
				DrawLineEx(Vector2{wall.getA().x, wall.getA().y}, Vector2{wall.getB().x, wall.getB().y}, 2, GREEN);
			}			
			// Draw Rays
			float length_ray = 100;
			Vector2 center{rays[0].getPos().x, rays[0].getPos().y};
			DrawCircleV(center, 5, RED);
			
			for (raycast::Ray ray : rays)
			{	
				raycast::Point closest{ray.getPos().x+ray.getDirX()*length_ray, ray.getPos().y+ray.getDirY()*length_ray};
				float closestDist = length_ray;
				for (raycast::Wall wall : walls) 
				{
					raycast::Point* collision = (ray.cast(wall));
					if (collision == NULL)
						continue;
					
					float dist = collision->dist(ray.getPos());

					if(dist < closestDist){
						closest = *collision;
						closestDist = dist;
					}
				}
				Vector2 end_ray{closest.x, closest.y};
				DrawLineEx(center, end_ray, 2, WHITE);;
			}	

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