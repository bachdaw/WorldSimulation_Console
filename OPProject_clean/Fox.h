#pragma once
#include "Animal.h"

class Fox : public Animal {
private:
	int FindWeakerNeighbor(World* world, const Organism* org);
public:
	Fox(const int n, const int m);
	void Action(World* w, Commands dir) override;
	~Fox() {};
};