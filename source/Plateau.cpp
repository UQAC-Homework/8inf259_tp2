#include "../include/Plateau.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "../include/string_utils.h"

#define COMMENT_CHAR '#'
#define CITY_START "VILLES"
#define LINKS_START "LIENS"

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
			const std::vector<std::string> tokens = split(line, DIVIDER_CHAR);
			
			if (tokens.size() < 3)
			{
				std::cerr << "Line has missing tokens: " << line << std::endl;
				return false;
			}
			
			std::cout << "Ville: " << line << std::endl;
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
