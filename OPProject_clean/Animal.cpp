#include "Animal.h"
#include "World.h"
#include <iostream>
#define NOT_FOUND -1

Position Animal::Move(Commands dir, World* world)
{
	if (dir == NON) dir = (Commands)(rand() % 8);

	Position dest_position = position;
	switch (dir)
	{
	case WEST:
		if (dest_position.x == 0) dest_position.x = 0;
		else dest_position.x--;
		break;
	case NORTH_WEST:
		if (dest_position.x == 0) dest_position.x = 0;
		else dest_position.x--;
		if (dest_position.y == 0) dest_position.y = 0;
		else dest_position.y--;
		break;
	case NORTH:
		if (dest_position.y == 0) dest_position.y = 0;
		else dest_position.y--;
		break;
	case NORTH_EAST:
		if (dest_position.x == world->getM() - 1) dest_position.x = world->getM() - 1;
		else dest_position.x++;
		if (dest_position.y == 0) dest_position.y = 0;
		else dest_position.y--;
		break;
	case EAST:
		if (dest_position.x == world->getM() - 1) dest_position.x = world->getM() - 1;
		else dest_position.x++;
		break;
	case SOUTH_EAST:
		if (dest_position.x == world->getM() - 1) dest_position.x = world->getM() - 1;
		else dest_position.x++;
		if (dest_position.y == world->getN() - 1) dest_position.y = world->getN() - 1;
		else dest_position.y++;
		break;
	case SOUTH:
		if (dest_position.y == world->getN() - 1) dest_position.y = world->getN() - 1;
		else dest_position.y++;
		break;
	case SOUTH_WEST:
		if (dest_position.x == 0) dest_position.x = 0;
		else dest_position.x--;
		if (dest_position.y == world->getN() - 1) dest_position.y = world->getN() - 1;
		else dest_position.y++;
		break;
	}

	return dest_position;
}

char Animal::Draw() const
{
	switch (type)
	{
	case SHEEP:
		return 's';
	case WOLF:
		return 'w';
	case FOX:
		return 'f';
	case TURTLE:
		return 't';
	case ANTELOPE:
		return 'a';
	case CYBER_SHEEP:
		return 'c';
	case HUMAN:
		return 'H';
	}
	return '0';
}

int Animal::positionToCell(const Position& pos, World* world)
{
	return pos.y * world->getM() + pos.x;
}

int Animal::FindFreeNeighbor(World* world, const Organism* org)
{
	const Position pos = org->position;
	for (int i = pos.y - 1; i < pos.y + 2; i++)
	{
		if ((i < 0) || (i > world->getN() - 1)) continue;
		for (int j = pos.x - 1; j < pos.x + 2; j++)
		{
			int grid_number = i * world->getM() + j;
			if ((j < 0) || (j > world->getM() - 1)) continue;
			if (world->cells[grid_number].isOccupied) continue;
			else return grid_number;
		}
	}
	return -1;
}

std::string Animal::speciesToString(Species sp)
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

void Animal::Breed(World* world, const int cell, Species kind)
{
	const int n = world->getN();
	const int m = world->getM();

	switch (kind)
	{
	case WOLF:
		world->organisms.push_back(new Wolf(n, m));
		break;
	case SHEEP:
		world->organisms.push_back(new Sheep(n, m));
		break;
	case FOX:
		world->organisms.push_back(new Fox(n, m));
		break;
	case TURTLE:
		world->organisms.push_back(new Turtle(n, m));
		break;
	case ANTELOPE:
		world->organisms.push_back(new Antelope(n, m));
		break;
	case CYBER_SHEEP:
		world->organisms.push_back(new Cyber_Sheep(n, m));
		break;
	}

	const int last_index = world->organisms.size() - 1;
	world->organisms[last_index]->position = world->cells[cell].position;
	world->cells[cell].isOccupied = true;
	world->cells[cell].occupant = world->organisms[last_index];
	
	world->comment = world->comment + "New animal of type: " + speciesToString(type)
		+ " at position " + world->cells[cell].occupant->position.toString() + "\n";
}

void Animal::Defense(World* world, Organism* attacker)
{
	world->comment = world->comment + "Defended!\n";

	const int attacker_cell = attacker->position.y * world->getM() + attacker->position.x;
	world->cells[attacker_cell].isOccupied = false;
	world->cells[attacker_cell].occupant = NULL;

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

void Animal::Overtake(World* world, Organism* occupant, Organism* attacker)
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

void Animal::Collision(Organism* occupant, Organism* attacker, World* world)
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
		if (occupant->strength > attacker->strength)
		{
			if (attacker->type == HUMAN) world->player_alive = false;
			Defense(world, attacker);
		}
		else
		{
			if (occupant->type == HUMAN) world->player_alive = false;
			Overtake(world, occupant, attacker);
		}
	}
}

void Animal::Action(World* world, Commands dir)
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