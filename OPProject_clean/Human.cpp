#include "Human.h"
#include "World.h"

Human::Human(const int n, const int m)
{
	initiative = 4;
	strength = 5;
	age = 0;
	allowed_to_move = false;
	position.x = (rand() % m);
	position.y = (rand() % n);
	type = HUMAN;
}

void Human::Action(World* world, Commands dir)
{
	this->allowed_to_move = false;
	if (dir == SPECIAL_ABILITY && world->getAbilityCnt() == 0)
	{
		world->comment = world->comment + "Purification!\n";
		world->resetAbilityCnt();
		Purification(world);
	}
	else
	{
		if (dir == SPECIAL_ABILITY)
		{
			world->comment = world->comment + "There is still cooldown for "
				+ std::to_string(world->getAbilityCnt()) + " rounds!\n";
		}
		const Position dest_position = Move(dir, world);

		const int actual_cell = positionToCell(position, world); //pos_before
		const int destiny_cell = positionToCell(dest_position, world); //pos_after

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

void Human::Purification(World* world)
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
			if (world->cells[grid_number].isOccupied && world->cells[grid_number].occupant != this)
			{
				for (int i = 0; i < world->organisms.size(); i++)
				{
					if ((world->organisms[i]->position == world->cells[grid_number].occupant->position)
						&& (world->organisms[i]->type == world->cells[grid_number].occupant->type))
					{
						world->comment = world->comment + "Organism " + speciesToString(world->organisms[i]->type)
							+ " has been terminated by human's purification at " + world->organisms[i]->position.toString() + "\n";

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