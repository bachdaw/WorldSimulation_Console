#pragma once
#include "Plant.h"

class Sow_thistle : public Plant {
public:
	Sow_thistle(const int n, const int m);
	void Action(World* world, Commands dir) override;
	~Sow_thistle() {};
};