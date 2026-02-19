#pragma once

#include <set>
#include "Ville.h"

class Plateau {
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