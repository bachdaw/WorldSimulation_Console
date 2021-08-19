#include "Sosnowkys_hogweed.h"
#include "World.h"
#define CHANCE_TO_SOW 4
#define NOT_FOUND -1

Sosnowkys_hogweed::Sosnowkys_hogweed(const int n, const int m)
{
	initiative = 0;
	strength = 10;
	age = 0;
	allowed_to_move = false;
	position.x = (rand() % m);
	position.y = (rand() % n);
	type = SOSNOWKYS_HOGWEED;
}

bool Sosnowkys_hogweed::isAttackable(Species type)
{
	switch (type)
	{
	case GRASS:
		return false;
	case SOW_THISTLE:
		return false;
	case GUARANA:
		return false;
	case BELLADONNA:
		return false;
	case SOSNOWKYS_HOGWEED:
		return false;
	case CYBER_SHEEP:
		return false;
	}

	return true;
}

void Sosnowkys_hogweed::TerminateNeighbourhood(World* world)
{
	int destiny = 0;
	const Position pos = this->position;

	for (int i = pos.y - 1; i < pos.y + 2; i++)
	{
		if ((i < 0) || (i > world->getN() - 1)) continue;
		for (int j = pos.x - 1; j < pos.x + 2; j++)
		{
			int grid_number = i * world->getM() + j;
			if ((j < 0) || (j > world->getM() - 1)) continue;
			if (world->cells[grid_number].isOccupied && isAttackable(world->cells[grid_number].occupant->type))
			{
				if (world->cells[grid_number].occupant->type == HUMAN) world->player_alive = false;
				for (int i = 0; i < world->organisms.size(); i++)
				{
					if ((world->organisms[i]->position == world->cells[grid_number].occupant->position)
						&& (world->organisms[i]->type == world->cells[grid_number].occupant->type))
					{
						world->comment = world->comment + "Animal " + speciesToString(world->organisms[i]->type)
							+ " has been terminated by hogweed at " + position.toString() + "\n";

						delete world->organisms[i];
						world->organisms.erase(world->organisms.begin() + i);
						break;
					}
				}
				world->cells[grid_number].occupant = NULL;
				world->cells[grid_number].isOccupied = false;
			}
		}
	}
}

void Sosnowkys_hogweed::Action(World* world, Commands dir)
{
	this->allowed_to_move = false;
	TerminateNeighbourhood(world);

	const int free_cell = FindFreeNeighbor(world, this);
	if (free_cell != NOT_FOUND)
	{
		int rand_number = (rand() % 100);
		if (rand_number <= CHANCE_TO_SOW) Sow(world, free_cell, type);
	}
}

void Sosnowkys_hogweed::Collision(Organism* occupant, Organism* attacker, World* world)
{
	world->comment = world->comment + "Collision between occupant: " + speciesToString(occupant->type)
		+ " at " + occupant->position.toString() + " with attacker: " + speciesToString(attacker->type)
		+ " at " + attacker->position.toString() + "\n";

	if (attacker->type == CYBER_SHEEP) Overtake(world, occupant, attacker);
	else
	{
		world->comment = world->comment + "Both organisms die!\n";
		if (attacker->type == HUMAN) world->player_alive = false;
		const int attacker_cell = attacker->position.y * world->getM() + attacker->position.x;

		world->cells[attacker_cell].occupant = NULL;
		world->cells[attacker_cell].isOccupied = false;

		const int occupant_cell = occupant->position.y * world->getM() + occupant->position.x;
		world->cells[occupant_cell].occupant = NULL;
		world->cells[occupant_cell].isOccupied = false;

		for (int i = 0; i < world->organisms.size(); i++)
		{
			if ((world->organisms[i]->position == occupant->position) && (world->organisms[i]->type == occupant->type))
			{
				delete world->organisms[i];
				world->organisms.erase(world->organisms.begin() + i);
				break;
			}
		}

		for (int i = 0; i < world->organisms.size(); i++)
		{
			if ((world->organisms[i]->position == attacker->position) && (world->organisms[i]->type == attacker->type))
			{
				delete world->organisms[i];
				world->organisms.erase(world->organisms.begin() + i);
				break;
			}
		}
	}
}

