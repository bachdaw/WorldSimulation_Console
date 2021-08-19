#pragma once
#include "Plant.h"

class Belladonna : public Plant {
public:
	Belladonna(const int n, const int m);
	void Collision(Organism* occupant, Organism* attacker, World* world) override;
	~Belladonna() {};
};
