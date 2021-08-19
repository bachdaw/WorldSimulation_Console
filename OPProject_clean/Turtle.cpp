#include "Turtle.h"
#include "World.h"
#define CHANCE_TO_MOVE 24
#define NOT_FOUND -1
#define STRENGTH_TO_REFLECT 5

Turtle::Turtle(const int n, const int m)
{
    initiative = 1;
	strength = 2;
	age = 0;
	allowed_to_move = false;
	position.x = (rand() % m);
	position.y = (rand() % n);
	type = TURTLE;
}

void Turtle::Action(World* world, Commands dir)
{
	this->allowed_to_move = false;

	int rand_number = (rand() % 100);
	if (rand_number <= CHANCE_TO_MOVE)
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
}

void Turtle::Collision(Organism* occupant, Organism* attacker, World* world)
{
	world->comment = world->comment + "Collision between occupant: " + speciesToString(occupant->type)
		+ " at " + occupant->position.toString() + " with attacker: " + speciesToString(attacker->type)
		+ " at " + attacker->position.toString() + "\n";

	if (attacker->type == occupant->type)
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
			else if (attacker->strength < STRENGTH_TO_REFLECT) world->comment = world->comment + "Turtle reflects attack!\n";
			else
			{
				if (occupant->type == HUMAN) world->player_alive = false;
				Overtake(world, occupant, attacker);
			}
		}
		else if (this == attacker)
		{
			if (occupant->strength < attacker->strength)
			{
				if (occupant->type == HUMAN) world->player_alive = false;
				Overtake(world, occupant, attacker);
			}
			else if (occupant->strength < STRENGTH_TO_REFLECT) world->comment = world->comment + "Turtle reflects attack!\n";

			else if (occupant->strength > attacker->strength)
			{
				if (attacker->type == HUMAN) world->player_alive = false;
				Defense(world, attacker);
			}
		}

	}
}