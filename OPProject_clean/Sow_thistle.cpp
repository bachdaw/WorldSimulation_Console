#include "Sow_thistle.h"
#include "World.h"
#define SOW_ATTEMPTS 3
#define NOT_FOUND -1
#define CHANCE_TO_SOW 4

Sow_thistle::Sow_thistle(const int n, const int m)
{
	initiative = 0;
	strength = 0;
	age = 0;
	allowed_to_move = false;
	position.x = (rand() % m);
	position.y = (rand() % n);
	type = SOW_THISTLE;
}
void Sow_thistle::Action(World* world, Commands dir)
{
	this->allowed_to_move = false;
	int free_cell = FindFreeNeighbor(world, this);

	if (free_cell != NOT_FOUND)
	{
		int rand_number;
		bool result = false;

		for (int i = 0; i < SOW_ATTEMPTS; i++)
		{
			rand_number = (rand() % 100);
			if (rand_number <= CHANCE_TO_SOW)
			{
				result = true;
				break;
			}
		}
		if (result) Sow(world, free_cell, type);
	}
}