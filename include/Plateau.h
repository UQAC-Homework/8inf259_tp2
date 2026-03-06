#pragma once

#include "Graphs/CityGraph.h"

class Plateau
{
	CityGraph _graph;
	std::size_t _currentEclosionCount;

public:
	Plateau();

	bool charger(const std::string& fichier);

	void actionPlacerTroisCubes();
	void actionInfecter();
	void actionPlacerRail();
	void actionPlusCourtChemin();
	void afficherEtat();

	void menu();
};
