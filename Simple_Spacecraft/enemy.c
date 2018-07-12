#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>
#include "config.h"
#include "timing.h"
#include "enemy.h"

void enemyConstructor(Object *evil, int n) {
	for (int i = 0; i < n; i++) {
		//evilConstructor(&evil[i]);
		//printf("%d\n", &evil[i]);
		(*(evil + i)).status = 0;
	}
}

int enemyGenerator(Object *evil, int ring) {
	// Search for location
	bool finder = true;
	if (ring == MAX_ENEMIES)
		ring = 0;
	int round = ring;
	do {
		//printf("%d\n",ring);
		if ((*(evil + ring)).status == 0) {
			srand(current_time_ms());
			// Create the enemy craft:
			(*(evil + ring)).size.h = 1 + rand() % EVIL_MAX_HEIGHT;
			(*(evil + ring)).size.w = 1 + rand() % EVIL_MAX_WIDTH;
			//(*(evil + ring)).status = (int *)malloc(sizeof(int));
			(*(evil + ring)).status = 1;

			// Create the enemy in Random position:
			(*(evil + ring)).pos.x = (float)rand() / (float)(RAND_MAX)* SCREEN_WIDTH;
			//printf("\n%d", (*(evil + ring)).status);
			(*(evil + ring)).pos.y = -1 * (*(evil + ring)).size.h - (float)rand() / (float)(RAND_MAX) *((*(evil + ring)).size.h * 4);
			// Set Random Speed
			(*(evil + ring)).speed.y = 0.56 + (float)rand() / (float)(RAND_MAX / 1.50);
			(*(evil + ring)).speed.x = 0;
			if (rand() % 10 == 10)
				(*(evil + ring)).speed.x = 0.26 + (float)rand() / (float)(RAND_MAX / 0.70);
			(*(evil + ring)).acc = 0.2;
			//printf("mem: %d, size: %.1f,%.f ; pos: %.2f,%.2f", &evil, (*(evil + ring)).size.w, (*(evil + ring)).size.h, (*(evil + ring)).pos.x, (*(evil + ring)).pos.y);
			ring++;
			return ring;
		}
		ring++;
		if (ring == round)
			return 0;
		if (ring == MAX_ENEMIES)
			ring = 0;
	} while (finder);
}

void enemyMovement(Object *evil) {
	(*evil).pos.y += (*evil).speed.y;
	(*evil).pos.x += (*evil).speed.x;
	(*evil).speed.y += GRAVITY;
}

void freeEnemy(Object *evil) {
	(*evil).status = 0;
}