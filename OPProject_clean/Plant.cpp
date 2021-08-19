#include "Plant.h"
#include "World.h"
#include <iostream>
#include <string>
#define CHANCE_TO_SOW 4
#define NOT_FOUND -1


int Plant::FindFreeNeighbor(World* world, const Organism* org)
{
	int origin = 0;
	const Position pos = org->position;

	for (int i = pos.y - 1; i < pos.y + 2; i++)
	{
		if ((i < 0) || (i > world->getN() - 1)) continue;
		for (int j = pos.x - 1; j < pos.x + 2; j++)
		{
			int grid_number = i * world->getM() + j;
			if ((j < 0) || (j > world->getM() - 1)) continue;
			if (world->cells[grid_number].isOccupied) continue;
			else
			{
				origin = grid_number;
				return origin;
			}
		}
	}
	return NOT_FOUND;
}

std::string Plant::speciesToString(Species sp)
{
	switch (sp)
	{
	case SHEEP:
		return "sheep";
	case WOLF:
		return "wolf";
	case FOX:
		return "fox";
	case TURTLE:
		return "turtle";
	case ANTELOPE:
		return "antelope";
	case CYBER_SHEEP:
		return "cyber sheep";
	case HUMAN:
		return "human";
	case GRASS:
		return "grass";
	case SOW_THISTLE:
		return "sow thistle";
	case GUARANA:
		return "guarana";
	case BELLADONNA:
		return "belladonna";
	case SOSNOWKYS_HOGWEED:
		return "sosnowkys hogweed";
	}
	return "NON";
}

void Plant::Sow(World* world, const int cell, Species kind)
{
	const int n = world->getN();
	const int m = world->getM();

	switch (this->type)
	{
	case GRASS:
		world->organisms.push_back(new Grass(n, m));
		break;
	case GUARANA:
		world->organisms.push_back(new Guarana(n, m));
		break;
	case SOW_THISTLE:
		world->organisms.push_back(new Sow_thistle(n, m));
		break;
	case BELLADONNA:
		world->organisms.push_back(new Belladonna(n, m));
		break;
	case SOSNOWKYS_HOGWEED:
		world->organisms.push_back(new Sosnowkys_hogweed(n, m));
		break;
	}

	const int last_index = world->organisms.size() - 1;
	world->organisms[last_index]->position = world->cells[cell].position;
	world->cells[cell].isOccupied = true;
	world->cells[cell].occupant = world->organisms[last_index];

	world->comment = world->comment + "New " + speciesToString(type) + " sowed at " +
		world->cells[cell].occupant->position.toString() + " from " + position.toString() + "\n";
}

void Plant::Overtake(World* world, Organism* occupant, Organism* attacker)
{
	world->comment = world->comment + "Overtake!\n";
	const int attacker_cell = attacker->position.y * world->getM() + attacker->position.x;
	world->cells[attacker_cell].isOccupied = false;
	world->cells[attacker_cell].occupant = NULL;

	const int occupant_cell = occupant->position.y * world->getM() + occupant->position.x;
	world->cells[occupant_cell].occupant = attacker;
	world->cells[occupant_cell].isOccupied = true;
	attacker->position = world->cells[occupant_cell].position;

	for (int i = 0; i < world->organisms.size(); i++)
	{
		if ((world->organisms[i]->position == occupant->position) && (world->organisms[i]->type == occupant->type))
		{
			delete world->organisms[i];
			world->organisms.erase(world->organisms.begin() + i);
			break;
		}
	}
}

char Plant::Draw() const
{
	switch (type)
	{
	case GRASS:
		return 'g';
	case SOW_THISTLE:
		return 'h';
	case GUARANA:
		return 'u';
	case BELLADONNA:
		return 'b';
	case SOSNOWKYS_HOGWEED:
		return 'y';
	}
	return '0';
}

void Plant::Collision(Organism* occupant, Organism* attacker, World* world)
{
	world->comment = world->comment + "Collision between occupant: " + speciesToString(occupant->type)
		+ " at " + occupant->position.toString() + " with attacker: " + speciesToString(attacker->type)
		+ " at " + attacker->position.toString() + "\n";

	Overtake(world, occupant, attacker);
}

void Plant::Action(World* world, Commands dir)
{
	this->allowed_to_move = false;
	
	const int free_cell = FindFreeNeighbor(world, this);
	if (free_cell != NOT_FOUND)
	{
		int rand_number = (rand() % 100);
		if (rand_number <= CHANCE_TO_SOW) Sow(world, free_cell, type);
	}
}
