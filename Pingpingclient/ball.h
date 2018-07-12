#pragma once
typedef struct Ball {
	Object Obj;

} Ball;

void newBall(Ball*);
void ballMovement(Ball*);
void is_collision(Ball*, Player*, Player*);
void startMovement(Ball*);