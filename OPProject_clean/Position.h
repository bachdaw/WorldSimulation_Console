#pragma once
#include <iostream>
#include <string>

struct Position {
	int x;
	int y;

	bool operator==(const Position& right)
	{
		if ((x == right.x) && (y == right.y)) return true;
		else return false;
	}

	std::string toString()
	{
		return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
	}

	friend std::ostream& operator<<(std::ostream& ostr, const Position& pos)
	{		
		ostr << "(" << pos.x << "," << pos.y << ")";
		return ostr;
	}
};

