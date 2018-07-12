#pragma once
#define WINDOW_TITLE "The Cleaner! v0.00000001bbbb"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TARGET_FRAME_RATE 60
#define CRAFT_WIDTH 10
#define CRAFT_HEIGHT 90
#define MAX_ENEMIES 600
#define DIFFICULTY 0.05
#define GRAVITY 0.01

typedef struct {
	unsigned short int status;
	struct speed
	{
		float x;
		float y;
	} speed;
	struct pos
	{
		float x;
		float y;
	} pos;
	struct size
	{
		float h;
		float w;
	} size;
	float acc;
	float friction;
} Object;