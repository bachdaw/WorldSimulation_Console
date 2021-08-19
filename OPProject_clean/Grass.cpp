#include "Grass.h"

Grass::Grass(const int n, const int m)
{
	initiative = 0;
	strength = 0;
	age = 0;
	allowed_to_move = false;
	position.x = (rand() % m);
	position.y = (rand() % n);
	type = GRASS;
}
