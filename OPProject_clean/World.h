#pragma once
#include "Animal.h"
#include "Plant.h"
#include "Cell.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"
#include "Cyber_Sheep.h"
#include "Grass.h"
#include "Guarana.h"
#include "Sow_thistle.h"
#include "Belladonna.h"
#include "Sosnowkys_hogweed.h"
#include "Human.h"
#include <vector>
#include <fstream>

class World {
private:
	int m;
	int n;
	int special_ability_cnt;

	Species toSpecies(const char t);
	void newOrganism(Species sp, const int cell);
	int loadGame();
	void saveGame();
	void makeTurn(Commands dir);
	void drawWorld();
public:
	bool failed_to_load;
	bool player_alive;
	std::vector<Organism*> organisms;
	Cell* cells;
	std::string comment;

	World();
	World(const int n, const int m);
	void resetAbilityCnt();
	int getAbilityCnt() const;
	int getM() const;
	int getN() const;
	void game();
	~World();
};
