#include "../include/Ville.h"

Ville::Ville()
{
}

Ville::Ville(const std::string& nom, const std::string& couleur, bool port)
{
	this->nom = nom;
	this->couleur = couleur;
	this->port = port;
}
