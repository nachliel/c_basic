#include "config.h"
#include "player.h"

/*
Create new Player
*/
void newPlayer(Player *player) {
	player->key.up = false;
	player->key.down = false;
	player->key.left = false;
	player->key.right = false;

	player->Obj.w = PL_WIDTH;
	player->Obj.h = PL_HEIGHT;

	player->Obj.y = SCREEN_HEIGHT / 2;
	player->Obj.x = player->Obj.w + 0.0;

	player->Obj.dx = 0;
	player->Obj.dy = 0;
	player->score = 0;
}

void playerMovement(Player *player, Keys keys) {
	//  Player Movement:
	if (keys.up & player->Obj.y > 0)
		player->Obj.dy = -1*SPEED;
	else
		if (keys.down  & (player->Obj.y + player->Obj.h < SCREEN_HEIGHT))
			player->Obj.dy = SPEED;
		else
			player->Obj.dy = 0;

	if (keys.left & (player->Obj.x > 0))
		player->Obj.dx = -1*SPEED;
	else
		if (keys.right & (player->Obj.x + player->Obj.w < SCREEN_WIDTH))
			player->Obj.dx = SPEED;
		else
			player->Obj.dx = 0;

	player->Obj.x += player->Obj.dx;
	player->Obj.y += player->Obj.dy;
}
