#pragma once
#include "Animal.h"

class Turtle : public Animal {
public:
	Turtle(const int n, const int m);
	void Action(World* w, Commands dir) override;
	void Collision(Organism* occupant, Organism* attacker, World* world) override;
	~Turtle() {};
};