#pragma once
#include <iostream>
#include "Position.h"
#include "Enums.h"

class World;

class Organism {
public:
	Position position;
	Species type;
	int strength;
	int age;
	int initiative;
	bool allowed_to_move;

	Organism() {};
	virtual char Draw() const = 0;
	virtual void Collision(Organism* occupant, Organism* attacker, World* world) {};
	virtual void Action(World* world, Commands dir) = 0;
	~Organism() {};
};
