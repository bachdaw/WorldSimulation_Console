#include "Sheep.h"

Sheep::Sheep(const int n, const int m)
{
	initiative = 4;
	strength = 4;
	age = 0;
	allowed_to_move = false;
	position.x = (rand() % m);
	position.y = (rand() % n);
	type = SHEEP;
}