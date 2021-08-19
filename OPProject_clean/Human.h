#pragma once
#include "Animal.h"

class Human : public Animal {
public:
	Human(const int n, const int m);
	void Action(World* world, Commands dir) override;
	void Purification(World* world);
	~Human() {};
};