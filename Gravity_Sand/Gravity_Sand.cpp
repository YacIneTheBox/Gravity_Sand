#include <iostream>
#include "raylib.h"

typedef struct SandParticle {
	float x, y;         // Position
	float vx, vy;       // Velocity 
	bool active;      // Is the particle active (falling) or settled
} SandParticle;

void GravityForce(SandParticle& p);
int main()
{
	const int screenWidth = 800;
	const int screenHeight = 600;
	const int NUM_PARTICULES = 100;

	InitWindow(screenWidth, screenHeight, "Gravity Sand Simulation");
	SetTargetFPS(60);

	SandParticle particules[NUM_PARTICULES]; // Array to hold sand particles

	// Initialize particles
	for (int i = 0; i < NUM_PARTICULES; i++) {
		particules[i].x = screenWidth / 2 + (rand() % 100 - 50); // Random x position around center
		particules[i].y = rand() % 50; // Start near the top
		particules[i].vx = 0;
		particules[i].vy = 0;
		particules[i].active = false;
	}

	int cmpt_particule = 0; // Counter to control particle activation
	while(!WindowShouldClose())
	{
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && cmpt_particule < NUM_PARTICULES) {
			// Activate a new particle
			particules[cmpt_particule].x = GetMouseX();
			particules[cmpt_particule].y = GetMouseY();
			particules[cmpt_particule].vx = 0;
			particules[cmpt_particule].vy = 0;
			particules[cmpt_particule].active = true;
			cmpt_particule = (cmpt_particule + 1) % NUM_PARTICULES; // Loop back to start
		}

		// Update particle positions
		for (int i = 0; i < NUM_PARTICULES; i++) {

			if (particules[i].y < screenHeight){
				particules[i].x += particules[i].vx;
				particules[i].y += particules[i].vy;
			}

			if (particules[i].y >= screenHeight) {
				particules[i].y = screenHeight;
				particules[i].vy = 0; // Settle the particle
			}

		}

		BeginDrawing();
		ClearBackground(BLACK);

		// Update and draw particles
		for (int i = 0; i < NUM_PARTICULES; i++) {
			if (particules[i].active){
				DrawRectangle(particules[i].x, particules[i].y, 5, 5, YELLOW);
				GravityForce(particules[i]);
			}
		}

		EndDrawing();
	}
}

void GravityForce(SandParticle &p) {
	const float gravity = 0.5f; // Gravity acceleration
	p.vy += gravity;
}


