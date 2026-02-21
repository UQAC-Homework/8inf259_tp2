#pragma once

#include "Graphs/CityGraph.h"

class Plateau
{
	CityGraph _graph;

public:
	Plateau();

	/// Loads the map from the file
	bool charger(const std::string& fichier);
	void actionPlacerTroisCubes();
	void actionInfecter();
	void actionPlacerRail();
	void actionPlusCourtChemin();
	void afficherEtat();
	void menu();
};
