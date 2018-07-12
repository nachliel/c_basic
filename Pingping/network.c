#include "config.h"
#include "network.h"

char* buildNetworkBuffer(Keys* keys) {
	char *final = (char*)malloc(6, sizeof(char));
	if (keys->up)
		final[0] = '1';
	else
		final[0] = '0';
	if (keys->down)
		final[1] = '1';
	else
		final[1] = '0';
	if (keys->left)
		final[2] = '1';
	else
		final[2] = '0';
	if (keys->right)
		final[3] = '1';
	else
		final[3] = '0';
	if (keys->space)
		final[4] = '1';
	else
		final[4] = '0';

	final[5] = '\0';
	return final;
}

void convertBuffer(char* buffer, Keys* keys) {

	if (buffer[0] == '1')
		keys->up = true;
	else
		keys->up = false;

	if (buffer[1] == '1')
		keys->down = true;
	else
		keys->down = false;

	if (buffer[2] == '1')
		keys->left = true;
	else
		keys->left = false;

	if (buffer[3] == '1')
		keys->right = true;
	else
		keys->right = false;
	if (buffer[4] == '1')
		keys->space = true;
	else
		keys->space = false;
}