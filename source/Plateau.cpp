#include "../include/Plateau.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "../include/string_utils.h"

#define COMMENT_CHAR '#'

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
	
	std::string line;
	while (std::getline(stream, line))
	{
		line = trim(line);
		
		if (line.empty())
			continue;
		
		if (line.at(0) == COMMENT_CHAR)
			continue;

		std::cout << line << std::endl;
	}
	
	stream.close();
	return true;
}

void Plateau::menu()
{
}
