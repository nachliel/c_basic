#include "config.h"

void resetKeyboard(Keys *keys) {
	keys->down = false;
	keys->right = false;
	keys->left = false;
	keys->up = false;
}