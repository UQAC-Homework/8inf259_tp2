#include "../include/Plateau.h"

#include <cassert>
#include <climits>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "../include/Graph.h"
#include "../include/GraphParser.h"

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

	try
	{
		Graph graph = loadFromStream(stream);
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
