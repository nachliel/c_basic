#pragma once
#define PL_WIDTH 10
#define PL_HEIGHT 60
#define SPEED 2

typedef struct Player {
	Object Obj;
	char* name;
	int score;
	unsigned short int status;
	Keys key;
} Player;

void newPlayer(Player* player);
void playerMovement(Player* player, Keys keys);
