#pragma once

#include <set>
#include "Ville.h"

class Plateau {
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