#pragma once

typedef struct {
	bool up;
	bool down;
	bool left;
	bool right;
} Keyboard;

void craftConstructor(Object *craft, Keyboard *keys);
void craftMovement(Object *craft, Keyboard keys);