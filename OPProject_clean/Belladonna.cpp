#include "Belladonna.h"
#include "World.h"

Belladonna::Belladonna(const int n, const int m)
{
	initiative = 0;
	strength = 99;
	age = 0;
	allowed_to_move = false;
	position.x = (rand() % m);
	position.y = (rand() % n);
	type = BELLADONNA;
}

void Belladonna::Collision(Organism* occupant, Organism* attacker, World* world)
{
	world->comment = world->comment + "Collision between occupant: " + speciesToString(occupant->type)
		+ " at " + occupant->position.toString() + " with attacker: " + speciesToString(attacker->type)
		+ " at " + attacker->position.toString() + "\n";
	world->comment = world->comment + "Both organisms die!\n";
		
	if (attacker->type == HUMAN) world->player_alive = false;
	int attacker_cell = attacker->position.y * world->getM() + attacker->position.x;

	world->cells[attacker_cell].occupant = NULL;
	world->cells[attacker_cell].isOccupied = false;

	int occupant_cell = occupant->position.y * world->getM() + occupant->position.x;
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