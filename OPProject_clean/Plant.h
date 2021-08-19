#pragma once
#include "Organism.h"

class Plant : public Organism {
protected:
	int FindFreeNeighbor(World* world, const Organism* org);
	std::string speciesToString(Species sp);
	void Sow(World* world, const int cell, Species kind);
	void Overtake(World* world, Organism* occupant, Organism* attacker);
	char Draw() const override;
	void Collision(Organism* occupant, Organism* attacker, World* world) override;
public:
	Plant() {};
	void Action(World* world, Commands dir) override;
	~Plant() {};
};
