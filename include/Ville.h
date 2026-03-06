#pragma once
#include <map>
#include <string>
#include <vector>

class Ville
{
public:
	std::string nom;
	std::string couleur;
	bool port;
	std::map<std::string, int> cubes;
	std::vector<std::string> voisins;

	Ville();
	Ville(const std::string& nom, const std::string& couleur, bool port);

	int totalCubes() const;
	int cubesDe(const std::string& couleur) const;
};
