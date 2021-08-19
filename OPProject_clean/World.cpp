#include "World.h"
#include "Sort.h"
#include <math.h>
#include <conio.h>
#define ORGANISMS_LOWER_LIMIT 50
#define COOLDOWN 5
#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
#define Z 122
#define S 115
#define L 108
#define Q 113
#define RESET   "\033[0m"
#define BOLDBLUE    "\033[1m\033[34m"
#pragma warning(disable : 4996)

World::World()
{
	system("cls");
	failed_to_load = false;
	if (loadGame() == -1) failed_to_load = true;
}

World::World(int n, int m)
	:n(n), m(m)
{
	comment = "";
	failed_to_load = false;

	cells = new Cell[n * m];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cells[(m * i) + j].position.x = j;
			cells[(m * i) + j].position.y = i;
			cells[(m * i) + j].occupant = NULL;
			cells[(m * i) + j].isOccupied = false;
		}
	}

	player_alive = true;
	special_ability_cnt = 0;
	organisms.push_back(new Human(n, m));
	const int human_pos = organisms[0]->position.y * m + organisms[0]->position.x;
	cells[human_pos].isOccupied = true;
	cells[human_pos].occupant = organisms[0];

	int organisms_number = sqrt(m * n) * 3;
	if ((m * n) == 1) organisms_number = 1;
	else if (organisms_number >= (m * n)) organisms_number /= 2;

	if (n * m < ORGANISMS_LOWER_LIMIT)
	{
		for (int i = 1; i < organisms_number; i++)
		{
			Species rand_species = (Species)(rand() % 11);
			newOrganism(rand_species, -1);
		}
	}
	else
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 2; j++)
				newOrganism((Species)i, -1);
		}

		const int diff = organisms_number - 22; 
		for (int i = 0; i < diff; i++)
		{
			Species rand_species = (Species)(rand() % 11);
			newOrganism(rand_species, -1);
		}
	}
}

Species World::toSpecies(const char t)
{
	switch (t)
	{
	case 'w':
		return WOLF;
	case 's':
		return SHEEP;
	case 'f':
		return FOX;
	case 't':
		return TURTLE;
	case 'a':
		return ANTELOPE;
	case 'c':
		return CYBER_SHEEP;
	case 'g':
		return GRASS;
	case 'h':
		return SOW_THISTLE;
	case 'u':
		return GUARANA;
	case 'b':
		return BELLADONNA;
	case 'y':
		return SOSNOWKYS_HOGWEED;
	case 'H':
		return HUMAN;
	}
	return WOLF;
}

void World::newOrganism(Species sp, const int cell)
{
	switch (sp)
	{
	case WOLF:
		organisms.push_back(new Wolf(n, m));
		break;
	case SHEEP:
		organisms.push_back(new Sheep(n, m));
		break;
	case FOX:
		organisms.push_back(new Fox(n, m));
		break;
	case TURTLE:
		organisms.push_back(new Turtle(n, m));
		break;
	case ANTELOPE:
		organisms.push_back(new Antelope(n, m));
		break;
	case CYBER_SHEEP:
		organisms.push_back(new Cyber_Sheep(n, m));
		break;
	case GRASS:
		organisms.push_back(new Grass(n, m));
		break;
	case SOW_THISTLE:
		organisms.push_back(new Sow_thistle(n, m));
		break;
	case GUARANA:
		organisms.push_back(new Guarana(n, m));
		break;
	case BELLADONNA:
		organisms.push_back(new Belladonna(n, m));
		break;
	case SOSNOWKYS_HOGWEED:
		organisms.push_back(new Sosnowkys_hogweed(n, m));
		break;
	case HUMAN:
		organisms.push_back(new Human(n, m));
		break;
	}

	const int last_index = organisms.size() - 1;
	int help_pos;
	if (cell == -1)
	{
		help_pos = (organisms[last_index]->position.y * m) + organisms[last_index]->position.x;

		while (cells[help_pos].isOccupied)
		{
			organisms[last_index]->position.x = (rand() % m);
			organisms[last_index]->position.y = (rand() % n);
			help_pos = (organisms[last_index]->position.y * m) + organisms[last_index]->position.x;
		}
	}
	else help_pos = cell;
	cells[help_pos].isOccupied = true;
	cells[help_pos].occupant = organisms[last_index];
	organisms[last_index]->position = cells[help_pos].position;
}

int World::loadGame()
{
	delete[] cells;
	cells = NULL;
	std::vector<Organism*>().swap(organisms);

	std::ifstream file("settings.txt");
	if (!file.good())
	{
		file.close();
		std::cout << "The settings file does not exist!" << std::endl;
		system("PAUSE");
		return -1;
	}

	int m, n, ab;
	char pa;
	file >> m >> n >> ab >> pa;
	if (!file.good())
	{
		file.close();
		std::cout << "Wrong format of file!" << std::endl;
		return -1;
	}

	this->m = m;
	this->n = n;

	cells = new Cell[n * m];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cells[(m * i) + j].position.x = j;
			cells[(m * i) + j].position.y = i;
			cells[(m * i) + j].occupant = NULL;
			cells[(m * i) + j].isOccupied = false;
		}
	}

	special_ability_cnt = ab;
	if (pa == 'f') player_alive = false;
	else if (pa == 't') player_alive = true;
	else
	{
		file.close();
		std::cout << "Wrong format of file!" << std::endl;
		return -1;
	}

	int cell_index, strength, age;
	char type;
	while (file >> cell_index >> type >> strength >> age)
	{
		if (file.eof()) break;
		if (!file.good())
		{
			file.close();
			std::cout << "Wrong format of file!" << std::endl;
			return -1;
		}
		else
		{
			newOrganism(toSpecies(type), cell_index);
			const int last_index = organisms.size() - 1;
			organisms[last_index]->strength = strength;
			organisms[last_index]->age = age;
		}
	}
	file.close();
	return 0;
}

void World::saveGame()
{
	std::ofstream file;
	file.open("settings.txt", std::ofstream::out | std::ofstream::trunc);

	file << m << " " << n << " " << special_ability_cnt << " ";
	if (player_alive == false) file << "f" << std::endl;
	else file << "t" << std::endl;

	for (int i = 0; i < n * m; i++)
	{
		if (cells[i].isOccupied)
		{
			file << i << " " << cells[i].occupant->Draw() << " " << cells[i].occupant->strength
				<< " " << cells[i].occupant->age << std::endl;
		}
	}
	file.close();
}

void World::makeTurn(Commands dir)
{
	Sort(organisms, 0, organisms.size() - 1);
	for (int i = 0; i < organisms.size(); i++) {
		organisms[i]->allowed_to_move = true;
	}
	int display_cooldown = special_ability_cnt;
	if (player_alive && special_ability_cnt > 0)
	{
		special_ability_cnt--;
		display_cooldown = special_ability_cnt;
	}
	else if (player_alive && special_ability_cnt == 0 && dir == SPECIAL_ABILITY)
		display_cooldown = COOLDOWN;

	if (player_alive == true)
	{
		comment = comment
			+ "Z - Special ability (Cooldown: " + std::to_string(display_cooldown) + " rounds)\n"
			+ "L - Load save\n"
			+ "S - Save game\n"
			+ "Q - Quit game\n\n";
	}
	else
	{
		comment = comment
			+ "Z - Special ability (Player is dead!)\n"
			+ "L - Load save\n"
			+ "S - Save game\n"
			+ "Q - Quit game\n\n";
	}

	int size = organisms.size();
	for (int i = 0; i < size; i++)
	{
		if (i >= organisms.size()) break;
		for (int j = 0; j < size; j++)
		{
			if (j >= organisms.size()) break;
			if (organisms[j]->allowed_to_move == true)
			{
				if (organisms[j]->type == HUMAN)
					organisms[j]->Action(this, dir);
				else
					organisms[j]->Action(this, NON);
				break;
			}
		}
	}

	size = organisms.size();
	for (int i = 0; i < size; i++)
	{
		organisms[i]->age++;
	}

}
void World::drawWorld()
{
	for (int i = 0; i < (n * 2) + 1; i++)
	{
		for (int j = 0; j < (m * 2) + 1; j++)
		{
			if (i % 2 == 0)
			{
				if (j % 2 == 0) std::cout << "-";
				else std::cout << "---";
			}
			else
			{
				if (j % 2 == 0) std::cout << "|";
				else
				{
					char symbol = ' ';
					int curr_pos = ((i / 2) * m) + j / 2;
					if (cells[curr_pos].isOccupied) symbol = cells[curr_pos].occupant->Draw();
					if (cells[curr_pos].isOccupied && cells[curr_pos].occupant->type == HUMAN)
						std::cout << " " << BOLDBLUE << symbol << RESET << " ";
					else std::cout << " " << symbol << " ";
				}
			}
		}
		std::cout << std::endl;
	}
}

void World::resetAbilityCnt()
{
	special_ability_cnt = COOLDOWN;
}

int World::getAbilityCnt() const
{
	return special_ability_cnt;
}

int World::getM() const
{
	return m;
}

int World::getN() const
{
	return n;
}

Commands ConvertKey()
{
	int c = getch();
	int ex;
	if (c && c != 224)
	{
		switch (c)
		{
		case Z:
			return SPECIAL_ABILITY;
		case L:
			return LOAD_SAVE;
		case S:
			return SAVE_GAME;
		case Q:
			return QUIT;
		default:
			return NON;
		}
		return NON;
	}
	else
	{
		switch (ex = getch())
		{
		case KEY_UP:
			return NORTH;
		case KEY_DOWN:   
			return SOUTH;
		case KEY_LEFT:  
			return WEST;
		case KEY_RIGHT: 
			return EAST;
		default:
			return NON;
		}
	}
	return NON;
}

void World::game()
{
	system("cls");
	drawWorld();
	if (player_alive == true)
	{
		comment = comment
			+ "Z - Special ability (Cooldown: " + std::to_string(special_ability_cnt) + " rounds)\n"
			+ "L - Load save\n"
			+ "S - Save game\n"
			+ "Q - Quit game\n\n";
	}
	else
	{
		comment = comment
			+ "Z - Special ability (Player is dead!)\n"
			+ "L - Load save\n"
			+ "S - Save game\n"
			+ "Q - Quit game\n\n";
	}
	std::cout << comment;
	comment = "";

	Commands dir = NON;
	bool quit = false;
	while (!quit)
	{
		dir = NON;
		if (player_alive == true)
		{
			while (dir == NON)
				dir = ConvertKey();
		}
		else dir = ConvertKey();

		if (dir == QUIT)
		{
			break;
		}
		else if (dir == SAVE_GAME) saveGame();
		else if (dir == LOAD_SAVE)
		{
			if (loadGame() == -1)
			{
				system("cls");
				std::cout << "Wrong file format! Proceed to menu." << std::endl;
				system("PAUSE");
				failed_to_load = true;
				break;
			}
		}

		system("cls");
		if ((dir != SAVE_GAME) && (dir != LOAD_SAVE)) makeTurn(dir);
		else
		{
			if(dir == SAVE_GAME) comment = comment + "Game has been saved to file!\n";
			else if (dir == LOAD_SAVE) comment = comment + "Game has been loaded from file!\n";
		}

		drawWorld();
		std::cout << comment;
		comment = "";
	}
}

World::~World()
{
	if (cells != NULL) delete[] cells;
	std::vector<Organism*>().swap(organisms);
}

