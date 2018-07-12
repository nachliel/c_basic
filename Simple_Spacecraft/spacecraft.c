#include <stdbool.h>
#include <math.h>
#include <SDL.h>
#include "config.h"
#include "spacecraft.h"

void craftConstructor(Object *craft, Keyboard *keys) {
	(*keys).up = false;
	(*keys).down = false;
	(*keys).left = false;
	(*keys).right = false;
	(*craft).pos.x = 50;
	(*craft).pos.y = 50;
	(*craft).size.h = CRAFT_HEIGHT;
	(*craft).size.w = CRAFT_WIDTH;
	(*craft).speed.x = 0.0;
	(*craft).speed.y = 0.0;
	(*craft).acc = 6;
	(*craft).friction = 2;
}

void craftMovement(Object *craft, Keyboard keys) {
	//  Spacecraft Movement:
	/*
	if (keys.up)
		(*craft).speed.y -= (*craft).friction;
	if (keys.down)
		(*craft).speed.y += (*craft).friction;
	if (keys.left)
		(*craft).speed.x -= (*craft).friction;
	if (keys.right)
		(*craft).speed.x += (*craft).friction;
	
	// Friction:
	if (!keys.up && !keys.down) {
		if ((*craft).speed.y >= (*craft).friction)
			(*craft).speed.y -= (*craft).friction;
		else if ((*craft).speed.y <= (-1 * (*craft).friction))
			(*craft).speed.y += (*craft).friction;
		if (abs((*craft).speed.y) < (*craft).friction)
			(*craft).speed.y = 0.0;
	}
	if (!keys.left && !keys.right) {
		if ((*craft).speed.x > 0.0)
			(*craft).speed.x -= (*craft).friction;
		else if ((*craft).speed.x < 0.0)
			(*craft).speed.x += (*craft).friction;

		if (abs((*craft).speed.x) < (*craft).friction)
			(*craft).speed.x = 0.0;
	}*/
	if (keys.up)
		(*craft).speed.y = -1*(*craft).acc;
	else
		if (keys.down)
			(*craft).speed.y = (*craft).acc;
		else
			(*craft).speed.y =0;

	if (keys.left)
		(*craft).speed.x = -1*(*craft).acc;
	else
		if (keys.right)
			(*craft).speed.x = (*craft).acc;
		else
			(*craft).speed.x = 0;

	// Boundries:
	if ((*craft).pos.x + (*craft).size.w > SCREEN_WIDTH)
		(*craft).speed.x = -0.2;
	else if ((*craft).pos.x < 0)
		(*craft).speed.x = 0.2;
	if ((*craft).pos.y + (*craft).size.h > SCREEN_HEIGHT)
		(*craft).speed.y = -0.1;
	else if ((*craft).pos.y < 0)
		(*craft).speed.y = 0.1;

	// Update location:
	(*craft).pos.y += (*craft).speed.y;
	(*craft).pos.x += (*craft).speed.x;
	//boundry(craft); TEST ENTERING ADDRESS TO ANOTHER POINTER IN OTHER FUNCTION
}