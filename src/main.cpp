#include <iostream>
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
	InitWindow(screenWidth, screenHeight, "2D Raycasting");
	SetTargetFPS(60);


	// create vector of walls
	std::vector<raycast::Wall> walls;
	walls.push_back(raycast::Wall{screenWidth-10, 10, screenWidth-20, screenHeight-100});

	// create array of rays
	const int num_rays = 100;
	raycast::Ray rays[num_rays];
	raycast::Point ray_point{10, screenHeight/2};

	for (int a = 0; a < num_rays; a++)
	{
		rays[a].pos = &ray_point;
		rays[a].angle = (2*PI/num_rays)*a;
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
			ray_point.y -= 60/GetFPS();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			ray_point.y += 60/GetFPS();
		}

		if (IsKeyDown(KEY_LEFT))
		{
			ray_point.x -= 60/GetFPS();
		}
		if (IsKeyDown(KEY_RIGHT))
		{
			ray_point.x += 60/GetFPS();
		}
		printf("Ray coords: (%f, %f)\n", ray_point.x, ray_point.y);

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

			ClearBackground(BLACK);

			// Draw Walls
			for (raycast::Wall wall : walls)
			{
				DrawLineEx(Vector2{wall.a.x, wall.a.y}, Vector2{wall.b.x, wall.b.y}, 2, WHITE);
			}			
			// Draw Rays
			float length_ray = 200;
			Vector2 center{rays[0].pos->x, rays[0].pos->y};
			DrawCircleV(center, 5, RED);
			
			for (raycast::Ray ray : rays)
			{
				Vector2 end_ray{ray.pos->x+ray.getDirX()*length_ray, ray.pos->y+ray.getDirY()*length_ray};
				DrawLineEx(center, end_ray, 2, RED);;
			}	
			// raycast::Point* intersection = ray.cast(wall);

			// if (intersection != NULL)
			// {	
			// 	DrawCircle(intersection->x, intersection->y, 5, BLUE);
			// }
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------

	CloseWindow();                // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}