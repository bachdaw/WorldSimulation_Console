#include "World.h"
#include <iostream>
#include <conio.h>
#pragma warning(disable : 4996)

char Menu()
{
	std::cout << "1. New game" << std::endl;
	std::cout << "2. Load game" << std::endl;
	std::cout << "3. Credits" << std::endl;
	std::cout << "4. Quit" << std::endl;

	int c = 0;
	while (c == 0)
	{
		c = getch();
		if (c && c != 224)
		{
			switch (c)
			{
			case '1':
				return 1;
			case '2':
				return 2;
			case '3':
				return 3;
			case '4':
				return 4;
			default:
				return 0;
			}
			return 0;
		}
		system("cls");
	}
}

int main()
{
	srand(time(NULL));
	while (true)
	{
		system("cls");
		char command = Menu();
		if (command == 1)
		{
			system("cls");
			int n = 0;
			std::cout << "Enter n: ";
			std::cin >> n;
			while (!std::cin.good())
			{
				system("cls");
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Enter n: ";
				std::cout << "Wrong input!" << std::endl;
				std::cin >> n;
			}
			system("cls");
			int m = 0;
			std::cout << "Enter m: ";
			std::cin >> m;
			while (!std::cin.good())
			{
				system("cls");
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Wrong input!" << std::endl;
				std::cout << "Enter m: ";
				std::cin >> m;
			}

			World* world = new World(n, m);
			world->game();
			delete world;
		}
		else if (command == 2)
		{
			World* world = new World();
			if (!world->failed_to_load)
			{
				system("cls");
				std::cout << "Game has been loaded succesfully!" << std::endl;
				system("PAUSE");
				world->game();
				delete world;
			}
			else
			{
				system("cls");
				delete world;
				std::cout << "Wrong file format! Proceed to menu." << std::endl;
				system("PAUSE");
			}
			
		}
		else if (command == 3)
		{
			system("cls");
			std::cout << "This game was entirely made by Dawid Bach" << std::endl;
			std::cout << "(Well, maybe with a little help of stackoveflow :) )" << std::endl;
			std::cout << "II semester Data Engineering student index: 184629" << std::endl;
			system("PAUSE");
		}
		else if (command == 4) return 0;
	}
}