#include "Cyber_Sheep.h"

Cyber_Sheep::Cyber_Sheep(const int n, const int m)
{
	initiative = 4;
	strength = 11;
	age = 0;
	allowed_to_move = false;
	position.x = (rand() % m);
	position.y = (rand() % n);
	type = CYBER_SHEEP;
}
