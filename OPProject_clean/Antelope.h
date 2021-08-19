#pragma once
#include "Animal.h"

class Antelope : public Animal {
public:
	Antelope(const int n, const int m);
	void Action(World* w, Commands dir) override;
	void Collision(Organism* occupant, Organism* attacker, World* world) override;
	~Antelope() {};
private:
	Position Move(Commands dir, World* world);
};