#include "../include/Ville.h"

#include <ranges>

Ville::Ville()
{
}

Ville::Ville(const std::string& nom, const std::string& couleur, bool port)
{
	this->nom = nom;
	this->couleur = couleur;
	this->port = port;
}

void Ville::addCube(const std::string& color)
{
	if (this->cubes.contains(color))
		this->cubes[color]++;
	else
		this->cubes[color] = 1;
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
