#pragma once
#include "Plant.h"

class Sosnowkys_hogweed : public Plant {
private:
	bool isAttackable(Species type);
	void TerminateNeighbourhood(World* world);
public:
	Sosnowkys_hogweed(const int n, const int m);
	void Action(World* w, Commands dir) override;
	void Collision(Organism* occupant, Organism* attacker, World* world) override;
	~Sosnowkys_hogweed() {};
};
