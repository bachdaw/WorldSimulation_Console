#include "Fox.h"
#include "World.h"
#define NOT_FOUND -1

Fox::Fox(const int n, const int m)
{
	initiative = 7;
	strength = 3;
	age = 0;
	allowed_to_move = false;
	position.x = (rand() % m);
	position.y = (rand() % n);
	type = FOX;
}
void Fox::Action(World* world, Commands dir)
{
	this->allowed_to_move = false;
	const int actual_cell = positionToCell(position, world); //pos_before
	const int neighbor_cell = FindWeakerNeighbor(world, this);

	if (neighbor_cell != NOT_FOUND)
	{
		if (world->cells[neighbor_cell].isOccupied)
		{
			if (this->strength > world->cells[neighbor_cell].occupant->strength ||
				world->cells[neighbor_cell].occupant->type == BELLADONNA || 
				world->cells[neighbor_cell].occupant->type == SOSNOWKYS_HOGWEED)
				world->cells[neighbor_cell].occupant->Collision(world->cells[neighbor_cell].occupant, this, world);
			else
				Collision(world->cells[neighbor_cell].occupant, this, world);
		}
		else
		{
			world->cells[actual_cell].isOccupied = false;
			world->cells[actual_cell].occupant = NULL;

			world->cells[neighbor_cell].isOccupied = true;
			world->cells[neighbor_cell].occupant = this;
			this->position = world->cells[neighbor_cell].position;
		}
	}
}

int Fox::FindWeakerNeighbor(World* world, const Organism* org)
{
	const Position pos = org->position;

	for (int i = pos.y - 1; i < pos.y + 2; i++)
	{
		if ((i < 0) || (i > world->getN() - 1)) continue;
		for (int j = pos.x - 1; j < pos.x + 2; j++)
		{
			int grid_number = i * world->getM() + j;
			if ((j == position.x) && (i == position.y))
				continue;
			if ((j < 0) || (j > world->getM() - 1)) 
				continue;
			if (world->cells[grid_number].isOccupied && world->cells[grid_number].occupant->strength > this->strength)
				continue;
			else return grid_number;
		}
	}
	return -1;
}