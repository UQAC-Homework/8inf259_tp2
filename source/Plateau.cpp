#include "../include/Plateau.h"

#include <cassert>
#include <climits>
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

std::tuple<std::string, std::string> createLink(const std::string& line)
{
	const std::vector<std::string> tokens = split(line, DIVIDER_CHAR);

	if (tokens.size() < 2)
		throw std::out_of_range("Line has missing tokens: " + line);

	const std::string& origin = tokens.at(0);
	const std::string& destination = tokens.at(1);

	return {origin, destination};
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
	std::map<std::string, std::vector<std::string>> newLinks;

	try
	{
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
				throw std::logic_error("Unhandled line: " + line);

			assert((!processingCities && processingLinks) || (processingCities && !processingLinks));

			if (processingCities)
			{
				Ville newCity = createCity(line);
				newCities.insert({newCity.nom, newCity});
			}
			else
			{
				const auto newLink = createLink(line);

				const std::string origin = std::get<0>(newLink);
				const std::string destination = std::get<1>(newLink);

				if (newLinks.contains(origin))
					newLinks.at(origin).push_back(destination);
				else
					newLinks.insert({origin, {destination}});
			}
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		stream.close();
		return false;
	}

	stream.close();
	return true;
}

void Plateau::actionPlacerTroisCubes()
{
	throw std::logic_error("Not Implemented");
}

void Plateau::actionInfecter()
{
	throw std::logic_error("Not Implemented");
}

void Plateau::actionPlacerRail()
{
	throw std::logic_error("Not Implemented");
}

void Plateau::actionPlusCourtChemin()
{
	throw std::logic_error("Not Implemented");
}

void Plateau::afficherEtat()
{
	throw std::logic_error("Not Implemented");
}

void Plateau::menu()
{
	while (true)
	{
		std::cout << "\n";
		std::cout << "+======================================+" << std::endl;
		std::cout << "|       PANDEMIC IBERIA -- MENU        |" << std::endl;
		std::cout << "+======================================+" << std::endl;
		std::cout << "| 1. Placer 3 cubes sur une ville      |" << std::endl;
		std::cout << "| 2. Infecter une ville (+1 cube)      |" << std::endl;
		std::cout << "| 3. Placer un rail                    |" << std::endl;
		std::cout << "| 4. Plus court chemin                 |" << std::endl;
		std::cout << "| 5. Afficher l'etat du plateau        |" << std::endl;
		std::cout << "| 0. Quitter                           |" << std::endl;
		std::cout << "+======================================+" << std::endl;
		std::cout << "> Choix : ";

		int choice;

		if (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}

		switch (choice)
		{
		case 1:
			actionPlacerTroisCubes();
			break;
		case 2:
			actionInfecter();
			break;
		case 3:
			actionPlacerRail();
			break;
		case 4:
			actionPlusCourtChemin();
			break;
		case 5:
			afficherEtat();
			break;
		case 0:
			std::cout << "Au revoir !" << std::endl;
			return;
		default:
			std::cout << "Choix invalide." << std::endl;
		}
	}
}
