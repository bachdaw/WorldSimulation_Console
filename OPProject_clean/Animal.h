#pragma once
#include "Organism.h"
#include <stdlib.h>    
#include <time.h>     
#include <string>

class Animal : public Organism {
protected:
	Position Move(Commands dir, World* world);
	char Draw() const override;
	int positionToCell(const Position& pos, World* world);
	int FindFreeNeighbor(World* world, const Organism* org);
	std::string speciesToString(Species sp);
	void Breed(World* world, const int cell, Species kind);
	void Defense(World* world, Organism* attacker);
	void Overtake(World* world, Organism* occupant, Organism* attacker);
public:
	Animal() {};
	void Collision(Organism* occupant, Organism* attacker, World* world) override;
	void Action(World* world, Commands dir) override;
	~Animal() {};
};
