#include "../include/Ville.h"

#include <ranges>

Ville::Ville() : Ville("", "", false)
{
}

Ville::Ville(const std::string& nom, const std::string& couleur, bool port)
{
	this->nom = nom;
	this->couleur = couleur;
	this->port = port;
}

int Ville::totalCubes() const
{
	int total = 0;

	for (const auto count : this->cubes | std::views::values)
		total += count;

	return total;
}

int Ville::cubesDe(const std::string& couleur) const
{
	if (this->cubes.contains(couleur))
		return this->cubes.at(couleur);

	return 0;
}
