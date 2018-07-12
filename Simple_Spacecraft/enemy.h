#pragma once
#define EVIL_MAX_WIDTH 3
#define EVIL_MAX_HEIGHT 3
#define EVIL_MAX_SPEED 2.0

void enemyConstructor(Object *evil,int n);
/*Enemy Generator.
* Generates one enemy each time.
* Require enemy object array and ring
* Returns Ring of the next allocation for enemy.
*/
int enemyGenerator(Object *evil,int ring);
void enemyMovement(Object *evil);
void freeEnemy(Object *evil);