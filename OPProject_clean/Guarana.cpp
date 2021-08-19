#include "Guarana.h"
#include "World.h"
#define STRENGTH_INCREASE 3

Guarana::Guarana(const int n, const int m)
{
	initiative = 0;
	strength = 0;
	age = 0;
	allowed_to_move = false;
	position.x = (rand() % m);
	position.y = (rand() % n);
	type = GUARANA;
}

void Guarana::Collision(Organism* occupant, Organism* attacker, World* world)
{
	world->comment = world->comment + "Collision between occupant: " + speciesToString(occupant->type)
		+ " at " + occupant->position.toString() + " with attacker: " + speciesToString(attacker->type)
		+ " at " + attacker->position.toString() + "\n";

	Overtake(world, occupant, attacker);
	attacker->strength += STRENGTH_INCREASE;

	world->comment = world->comment + "Guarana eaten, strength of animal: " + speciesToString(attacker->type)
		+ " at " + attacker->position.toString() + " increased by 3!\n";

}