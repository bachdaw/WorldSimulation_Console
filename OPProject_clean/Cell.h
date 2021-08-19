#pragma once
#include "Position.h"

class Organism;

struct Cell {
	Position position;
	Organism* occupant;
	bool isOccupied;
};