#include "Wolf.h"

Wolf::Wolf(const int n, const int m)
{
	initiative = 5;
	strength = 9;
	age = 0;
	allowed_to_move = false;
	position.x = (rand() % m);
	position.y = (rand() % n);
	type = WOLF;
}