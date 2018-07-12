#pragma once
#include <stdbool.h>
#define WINDOW_TITLE "PingPong Host Network v0.1"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TARGET_FRAME_RATE 60
#define CRAFT_WIDTH 10
#define CRAFT_HEIGHT 90
#define MAX_ENEMIES 600
#define DIFFICULTY 0.05
#define GRAVITY 0.01

typedef struct {
	float x;
	float y;
	float dx;
	float dy;
	float h;
	float w;
} Object;

typedef struct {
	bool up;
	bool down;
	bool left;
	bool right;
	bool space;
} Keys;

void resetKeyboard(Keys *keys);