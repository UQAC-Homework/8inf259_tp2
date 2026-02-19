#pragma once

#include <map>
#include <string>
#include <vector>

class Ville {
public:
	/// Name of the city
	std::string nom;
	
	/// Color of the city
	std::string couleur;
	bool port;
	std::map<std::string, int> cubes;
	std::vector<std::string> voisins;

	Ville();
	Ville(const std::string& nom, const std::string& couleur, bool port);

	[[nodiscard]] int totalCubes() const;
	[[nodiscard]] int cubesDe(const std::string& couleur) const;
};