#include "../include/Plateau.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "../include/Graphs/CityGraph.h"
#include "../include/utils/graph.h"
#include "../include/utils/menu.h"
#include "../include/utils/pathfinding.h"

Plateau::Plateau() = default;

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
		this->_graph = utils::graph::loadGraphFromStream(stream);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		stream.close();
		return false;
	}

	std::cout << this->_graph.getCityCount() << " ville(s) chargée(s)." << std::endl;
	stream.close();
	return true;
}

void Plateau::actionPlacerTroisCubes()
{
	std::cout << "Veuillez choisir une ville à infecter:" << std::endl;
	const std::string city = utils::menu::chooseCity(
		std::cout,
		std::cin,
		this->_graph.getCityNames()
	);

	throw std::logic_error("Not Implemented");
}

void Plateau::actionInfecter()
{
	std::cout << "Veuillez choisir une ville à infecter:" << std::endl;
	const std::string city = utils::menu::chooseCity(
		std::cout,
		std::cin,
		this->_graph.getCityNames()
	);

	throw std::logic_error("Not Implemented");
}

void Plateau::actionPlacerRail()
{
	if (this->_graph.getRailsCount() >= 20)
	{
		std::cout << "La limite de 20 rails a déjà été atteinte." << std::endl;
		return;
	}

	std::cout << "Veuillez choisir une ville où placer un rail:" << std::endl;
	// TODO: Filter out cities that cannot have rails
	const std::string startCity = utils::menu::chooseCity(
		std::cout,
		std::cin,
		this->_graph.getCityNames()
	);

	std::cout << std::endl;
	std::cout << "Veuillez choisir où le rail se termine:" << std::endl;
	// TODO: Prevent rails to be placed where rails already exist
	const std::string endCity = utils::menu::chooseCity(
		std::cout,
		std::cin,
		this->_graph.getNeighbors(startCity, ROAD)
	);

	this->_graph.addRail(startCity, endCity);
}

void Plateau::actionPlusCourtChemin()
{
	ds::Set<std::string> cities = this->_graph.getCityNames();

	std::cout << "Veuillez choisir une ville de départ:" << std::endl;
	const std::string startCity = utils::menu::chooseCity(
		std::cout,
		std::cin,
		cities
	);

	cities.erase(startCity);

	std::cout << std::endl;
	std::cout << "Veuillez choisir une destination:" << std::endl;
	const std::string endCity = utils::menu::chooseCity(
		std::cout,
		std::cin,
		cities
	);

	std::cout << "=== " << startCity << " -> " << endCity << " ===" << std::endl;

	const std::vector<std::string> roadPath = utils::pathfinding::BFS(
		this->_graph,
		startCity,
		endCity,
		ROAD
	);
	const std::size_t roadActionCount = roadPath.size() - 1;

	std::cout << "[ROUTE] Terrestre uniquement (" << roadActionCount << " actions):" << std::endl;
	utils::menu::displayPath(std::cout, roadPath, this->_graph);

	const std::vector<std::string> roadAndRailsPath = utils::pathfinding::BFS(
		this->_graph,
		startCity,
		endCity,
		static_cast<TransportType>(ROAD | TRAIN)
	);
	const std::size_t roadAndRailsActionCount = roadAndRailsPath.size() - 1;

	std::cout << std::endl;
	std::cout << "[ROUTE + TRAIN] Terrestre + Rails (" << roadAndRailsActionCount << " actions):" << std::endl;
	utils::menu::displayPath(std::cout, roadAndRailsPath, this->_graph);
	std::cout << "=> Gain de " + std::to_string(roadActionCount - roadAndRailsActionCount) <<
		" action(s) grâce aux rails!" << std::endl;

	const std::vector<std::string> roadAndRailsAndBoatsPath = utils::pathfinding::BFS(
		this->_graph,
		startCity,
		endCity,
		ALL
	);
	const std::size_t roadAndRailsAndBoatsActionCount = roadAndRailsAndBoatsPath.size() - 1;

	std::cout << std::endl;
	std::cout << "[TOUT] Terrestre + Rails + Mer (" << roadAndRailsAndBoatsActionCount << " actions):" << std::endl;
	utils::menu::displayPath(std::cout, roadAndRailsAndBoatsPath, this->_graph);
	std::cout << "=> Gain de " + std::to_string(roadActionCount - roadAndRailsAndBoatsActionCount) <<
		" action(s) grâce au total!" << std::endl;
}

void Plateau::afficherEtat()
{
	throw std::logic_error("Not Implemented");
}

void Plateau::menu()
{
	const std::vector<std::tuple<int, std::string>> options = {
		{1, "Placer 3 cubes sur une ville"},
		{2, "Infecter une ville (+1 cube)"},
		{3, "Placer un rail"},
		{4, "Plus court chemin"},
		{5, "Afficher l'etat du plateau"},
		{0, "Quitter"},
	};

	while (true)
	{
		const int choice = utils::menu::askChoice(std::cout, std::cin, options);

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
