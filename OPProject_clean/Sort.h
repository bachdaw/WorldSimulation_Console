#pragma once
#include <vector>
#include "Organism.h"

void Swap(Organism** a, Organism** b)
{
	Organism* t = *a;
	*a = *b;
	*b = t;
}

int Partition(std::vector<Organism*>& orgs, int low, int high)
{
	Organism* pivot = orgs[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (orgs[j]->initiative == pivot->initiative)
		{
			if (orgs[j]->age > pivot->age)
			{
				i++;
				Swap(&orgs[i], &orgs[j]);
			}
		}
		else if (orgs[j]->initiative > pivot->initiative)
		{
			i++;
			Swap(&orgs[i], &orgs[j]);
		}
	}
	Swap(&orgs[i + 1], &orgs[high]);
	return (i + 1);
}

void Sort(std::vector<Organism*>& orgs, int low, int high)
{
	if (low < high)
	{
		int pi = Partition(orgs, low, high);

		Sort(orgs, low, pi - 1);
		Sort(orgs, pi + 1, high);
	}
}