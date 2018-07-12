#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>
#include "timing.h"
#include "config.h"
#include "spacecraft.h"
#include "enemy.h"

void renderer(Object *craft, SDL_Surface *screen, SDL_Surface *spaceShipSurface) {
	
	SDL_Rect rect;
	rect.x = (*craft).pos.x;
	rect.y = (*craft).pos.y;
	rect.h = (*craft).size.h;
	rect.w = (*craft).size.w;
	if ((*craft).status==2)
		SDL_FillRect(screen, &rect, SDL_MapRGB(spaceShipSurface->format, 0x67, 0x66, 0));
	else
		SDL_FillRect(screen, &rect, SDL_MapRGB(spaceShipSurface->format, 255, 255, 255));
}
bool is_collision(Object *craft_1, Object *craft_2) {
	if ((*craft_1).pos.x < (*craft_2).pos.x + (*craft_2).size.w &&
		(*craft_1).pos.x + (*craft_1).size.w >(*craft_2).pos.x &&
		(*craft_1).pos.y <  (*craft_2).pos.y + (*craft_2).size.h &&
		(*craft_1).size.h + (*craft_1).pos.y >(*craft_2).pos.y) {
		(*craft_2).speed.x = (*craft_1).speed.x;
		//(*craft_1).speed.x = ;
		(*craft_2).speed.y = (*craft_1).speed.y;
		//(*craft_1).speed.y = 0;
		return true;
	}
	else
		return false;
}


int main(void) 
{
	printf("Initalizing Video...\n");
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_Surface *spaceShipSurface = SDL_CreateRGBSurface(0, CRAFT_WIDTH, CRAFT_HEIGHT, 32, 0, 0, 0, 0);
	
	printf("Creating spacecraft...\n");
	//Setting up Objects:
	Object myCraft;
	myCraft.status = 2;
	Keyboard keys;
	Object enemy[MAX_ENEMIES];
	craftConstructor(&myCraft, &keys);
	printf("Creating enemies...\n");
	enemyConstructor(&enemy, MAX_ENEMIES);
	printf("Start Render...\n");
	// Message loop
	double totalTime = 0;
	const double targetInterval = 1000.0 / TARGET_FRAME_RATE;
	double interval = current_time_ms();
	bool running = true;
	SDL_Event e;
	double enemy_intervals = 1000;
	double last_enemy = 0;
	// ringing the enemy :)
	int ring = 0;
	int counter = 0;
	printf("~60 FPS");
	int tick = 0;
	while (running) {
		double elapsedMs = current_time_ms();
		float fps = 0;
		while (SDL_PollEvent(&e)) {
			// Handle incoming events
			switch (e.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN: {
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					keys.up = true;
					break;
				case SDLK_DOWN:		
					keys.down = true;
					break;
				case SDLK_LEFT:
					keys.left = true;
					break;
				case SDLK_RIGHT:
					keys.right = true;
					break;
				default:
					break;
				}
				break;
			}
			case SDL_KEYUP: {
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					keys.up = false;
					break;
				case SDLK_DOWN:
					keys.down = false;
					break;
				case SDLK_LEFT:
					keys.left = false;
					break;
				case SDLK_RIGHT:
					keys.right = false;
					break;
				default:
					break;
				}
				break;
			}	
			}
		}
		// Update
		tick++;

		totalTime += targetInterval;
		const double dx = sin(totalTime / 1000) * 60;

		// Spacecraft movement:
		craftMovement(&myCraft, keys);
		
		// Render Background
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
		
		// Render Spacecraft & Enemies
		renderer(&myCraft, screenSurface, spaceShipSurface);
		for (int i = 0; i < MAX_ENEMIES; i++) {
			if (enemy[i].status == 1) {
				if (enemy[i].pos.y < SCREEN_HEIGHT) {
					enemyMovement(&enemy[i]);
					renderer(&enemy[i], screenSurface, spaceShipSurface);
					// Check Collision
					is_collision(&myCraft, &enemy[i]);
					if (enemy[i].pos.x > SCREEN_WIDTH + 50.0 || enemy[i].pos.x < -50.0)
					{
						counter++;
						freeEnemy(&enemy[i]);
					}
				}
				else {
					freeEnemy(&enemy[i]);
					ring = i;
				}
			}
			
		}

		// Enemy Generator
		if (elapsedMs - last_enemy > enemy_intervals) {
			ring = enemyGenerator(&enemy,ring);
			last_enemy = elapsedMs;
			if (enemy_intervals >5)
				enemy_intervals = enemy_intervals - enemy_intervals * DIFFICULTY;
		}

		// Update window
		SDL_UpdateWindowSurface(window);

		// Timing
		if (tick == 60) {
			tick = 0;
			fps = 60 / ((elapsedMs - interval) / 1000);
			printf("\rfps: %.2f , Kicked: %d  ", fps, counter);
			interval = elapsedMs;
		}
		// Delayer: Keep 60 FPS
		elapsedMs = current_time_ms() - elapsedMs;
		const double sleepRequired = targetInterval - elapsedMs;
		if (sleepRequired > 0)
		{
			SDL_Delay(sleepRequired);
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}