#include <stdbool.h>
#include "config.h"
#include "player.h"
#include "ball.h"

void newBall(Ball* ball) {
	ball->Obj.x = SCREEN_WIDTH / 2;
	ball->Obj.y = SCREEN_HEIGHT / 2;
	ball->Obj.dx = 0.0;
	ball->Obj.dy = 0.0;
	ball->Obj.h = 5;
	ball->Obj.w = 5;
}

void ballMovement(Ball* ball) {
	ball->Obj.x += ball->Obj.dx;
	ball->Obj.y += ball->Obj.dy;
}

//void is_collision(Ball *ball, Player *player1, Player *player2);
void is_collision(Ball* ball, Player* player_1, Player* player_2) {
//  Wall collide:
	if (ball->Obj.y <= 0 || ball->Obj.y >= SCREEN_HEIGHT) {
		ball->Obj.dy = -1 * ball->Obj.dy;
	}
	
// Player 1 collide:
	if (ball->Obj.x + ball->Obj.w > player_1->Obj.x && ball->Obj.x + ball->Obj.w < player_1->Obj.x + player_1->Obj.w) {
		if (ball->Obj.y + ball->Obj.h > player_1->Obj.y && ball->Obj.y < player_1->Obj.y + player_1->Obj.h) {
			ball->Obj.dx = -1 * ball->Obj.dx;
			ball->Obj.dy = player_1->Obj.dy;
		
		}
	}
	else
		if (ball->Obj.x + ball->Obj.w > player_2->Obj.x && ball->Obj.x + ball->Obj.w < player_2->Obj.x + player_2->Obj.w) {
			if (ball->Obj.y + ball->Obj.h > player_2->Obj.y && ball->Obj.y < player_2->Obj.y + player_2->Obj.h) {
				ball->Obj.dx = -1 * ball->Obj.dx;
				ball->Obj.dy = player_2->Obj.dy;
			}
		}
}

void startMovement(Ball* ball) {
	newBall(ball);
	ball->Obj.dx = -2;
}