#pragma once

#include <map>
#include <string>
#include <vector>

class Ville
{
public:
	/// Name of the city
	std::string nom;

	/// Color of the city
	std::string couleur;
	bool port;
	std::vector<std::string> voisins;

	Ville();
	Ville(const std::string& nom, const std::string& couleur, bool port);

	/// Cubes accumulated by color on the city
	std::map<std::string, int> cubes;
	
	/// Adds a cube of the given color on the city
	void addCube(const std::string& color);

	/// Gets the amount of cubes stored on the city
	[[nodiscard]] int totalCubes() const;

	/// Gets the amount of cubes of a given color
	[[nodiscard]] int cubesDe(const std::string& couleur) const;
};
