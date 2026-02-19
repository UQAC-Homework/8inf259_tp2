#include "../include/Plateau.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "../include/string_utils.h"

#define COMMENT_CHAR '#'
#define DIVIDER_CHAR ';'
#define CITY_START "VILLES"
#define LINKS_START "LIENS"

Ville createCity(const std::string& line)
{
	const std::vector<std::string> tokens = split(line, DIVIDER_CHAR);

	if (tokens.size() < 3)
		throw std::out_of_range("Line has missing tokens: " + line);

	const std::string& name = tokens.at(0);
	const std::string& color = tokens.at(1);
	const std::string& isPort = tokens.at(2);

	Ville city(name, color, isPort == "1");

	return city;
}

Plateau::Plateau()
{
}

bool Plateau::charger(const std::string& fichier)
{
	if (!std::filesystem::exists(fichier))
	{
		std::cerr << "File does not exist at '" << fichier << "'." << std::endl;
		return false;
	}

	std::ifstream stream(fichier);

	std::map<std::string, Ville> newCities;
	bool processingCities = false;
	bool processingLinks = false;

	std::string line;
	while (std::getline(stream, line))
	{
		line = trim(line);

		if (line.empty())
			continue;

		if (line.at(0) == COMMENT_CHAR)
			continue;

		if (line == CITY_START)
		{
			processingCities = true;
			processingLinks = false;
			continue;
		}

		if (line == LINKS_START)
		{
			processingCities = false;
			processingLinks = true;
			continue;
		}

		if (!processingCities && !processingLinks)
		{
			std::cerr << "Unhandled line: " << line << std::endl;
			return false;
		}

		assert((!processingCities && processingLinks) || (processingCities && !processingLinks));

		if (processingCities)
		{
			Ville newCity = createCity(line);
			newCities.insert({newCity.nom, newCity});
		}
		else
		{
			std::cout << "Lien: " << line << std::endl;
		}
	}

	stream.close();
	return true;
}

void Plateau::menu()
{
}
