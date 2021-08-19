#include "Antelope.h"
#include "World.h"
#define CHANCE_TO_GET_AWAY 49
#define NOT_FOUND -1

Antelope::Antelope(const int n, const int m)
{
	initiative = 4;
	strength = 4;
	age = 0;
	allowed_to_move = false;
	position.x = (rand() % m);
	position.y = (rand() % n);
	type = ANTELOPE;
}
void Antelope::Action(World* world, Commands dir)
{
	this->allowed_to_move = false;
	const Position dest_position = Move(dir, world);

	const int actual_cell = positionToCell(position, world); 
	const int destiny_cell = positionToCell(dest_position, world); 

	if (actual_cell != destiny_cell)
	{
		if (world->cells[destiny_cell].isOccupied)
		{
			if (this->strength > world->cells[destiny_cell].occupant->strength ||
				world->cells[destiny_cell].occupant->type == BELLADONNA ||
				world->cells[destiny_cell].occupant->type == SOSNOWKYS_HOGWEED)
				world->cells[destiny_cell].occupant->Collision(world->cells[destiny_cell].occupant, this, world);
			else
				Collision(world->cells[destiny_cell].occupant, this, world);
		}
		else
		{
			this->position = dest_position;

			world->cells[actual_cell].isOccupied = false;
			world->cells[actual_cell].occupant = NULL;

			world->cells[destiny_cell].isOccupied = true;
			world->cells[destiny_cell].occupant = this;
		}
	}
}

void Antelope::Collision(Organism* occupant, Organism* attacker, World* world)
{
	world->comment = world->comment + "Collision between occupant: " + speciesToString(occupant->type)
		+ " at " + occupant->position.toString() + " with attacker: " + speciesToString(attacker->type)
		+ " at " + attacker->position.toString() + "\n";

	if (occupant->type == attacker->type)
	{
		int free_cell = FindFreeNeighbor(world, occupant);

		if (free_cell != NOT_FOUND) Breed(world, free_cell, this->type);
		else
		{
			free_cell = FindFreeNeighbor(world, attacker);

			if (free_cell != NOT_FOUND) Breed(world, free_cell, this->type);
		}
	}
	else
	{
		if (this == occupant)
		{
			if (occupant->strength > attacker->strength)
			{
				if (attacker->type == HUMAN) world->player_alive = false;
				Defense(world, attacker);
			}
			else
			{
				const int free_cell = FindFreeNeighbor(world, occupant);
				if (free_cell != NOT_FOUND)
				{
					world->comment = world->comment + "There is a chance for Antelope to get away!\n";

					int rand_number = (rand() % 100);
					if (rand_number >= CHANCE_TO_GET_AWAY)
					{
						int occupant_cell = positionToCell(occupant->position, world);

						world->comment = world->comment + "Success!\n";
						world->cells[free_cell].isOccupied = true;
						world->cells[free_cell].occupant = occupant;
						occupant->position = world->cells[free_cell].position;

						int attacker_cell = positionToCell(attacker->position, world);
						world->cells[occupant_cell].occupant = attacker;
						attacker->position = world->cells[occupant_cell].position;

						world->cells[attacker_cell].isOccupied = false;
						world->cells[attacker_cell].occupant = NULL;
					}
					else
					{
						world->comment = world->comment + "Failed!\n";
						Overtake(world, occupant, attacker);
					}
				}
				else
				{
					Overtake(world, occupant, attacker);
				}
			}
		}
		else if (this == attacker)
		{
			if (occupant->strength > attacker->strength)
			{
				const int free_cell = FindFreeNeighbor(world, occupant);
				if (free_cell != NOT_FOUND)
				{
					world->comment = world->comment + "There is a chance for Antelope to get away!\n";

					int rand_number = (rand() % 100);
					if (rand_number >= CHANCE_TO_GET_AWAY)
					{
						const int attacker_cell = positionToCell(attacker->position, world);
						world->comment = world->comment + "Success!\n";

						world->cells[attacker_cell].isOccupied = false;
						world->cells[attacker_cell].occupant = NULL;

						world->cells[free_cell].isOccupied = true;
						world->cells[free_cell].occupant = attacker;

						attacker->position = world->cells[free_cell].position;
					}
					else
					{
						world->comment = world->comment + "Failed!\n";
						Defense(world, attacker);
					}
				}
				else
				{
					world->comment = world->comment + "Failed!\n";
					Defense(world, attacker);
				}
			}
			else
			{
				if (occupant->type == HUMAN) world->player_alive = false;
				Overtake(world, occupant, attacker);
			}
		}
	}
}

Position Antelope::Move(Commands dir, World* world)
{
	if (dir == NON) dir = (Commands)(rand() % 8);

	Position dest_position = position;
	switch (dir)
	{
	case WEST:
		if (dest_position.x <= 2) dest_position.x = 0;
		else dest_position.x-=2;
		break;
	case NORTH_WEST:
		if (dest_position.x <= 2) dest_position.x = 0;
		else dest_position.x-=2;
		if (dest_position.y <= 2) dest_position.y = 0;
		else dest_position.y -= 2;
		break;
	case NORTH:
		if (dest_position.y <= 2) dest_position.y = 0;
		else dest_position.y -= 2;
		break;
	case NORTH_EAST:
		if (dest_position.x >= world->getM() - 3) dest_position.x = world->getM() - 1;
		else dest_position.x+=2;
		if (dest_position.y <= 2) dest_position.y = 0;
		else dest_position.y -= 2;
		break;
	case EAST:
		if (dest_position.x >= world->getM() - 3) dest_position.x = world->getM() - 1;
		else dest_position.x+=2;
		break;
	case SOUTH_EAST:
		if (dest_position.x >= world->getM() - 3) dest_position.x = world->getM() - 1;
		else dest_position.x+=2;
		if (dest_position.y >= world->getN() - 3) dest_position.y = world->getN() - 1;
		else dest_position.y+=2;
		break;
	case SOUTH:
		if (dest_position.y >= world->getN() - 3) dest_position.y = world->getN() - 1;
		else dest_position.y+=2;
		break;
	case SOUTH_WEST:
		if (dest_position.x <= 2) dest_position.x = 0;
		else dest_position.x-=2;
		if (dest_position.y >= world->getN() - 3) dest_position.y = world->getN() - 1;
		else dest_position.y+=2;
		break;
	}

	return dest_position;
}
