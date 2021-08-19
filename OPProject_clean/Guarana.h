#pragma once
#include "Plant.h"

class Guarana : public Plant {
public:
	Guarana(const int n, const int m);
	void Collision(Organism* occupant, Organism* attacker, World* world) override;
	~Guarana() {};
};
