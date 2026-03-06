#include "../include/Plateau.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>

#include "../include/Graphs/CityGraph.h"
#include "../include/utils/cities.h"
#include "../include/utils/graph.h"
#include "../include/utils/menu.h"
#include "../include/utils/pathfinding.h"

#define MAX_RAIL_COUNT 20
#define MAX_ECLOSION_COUNT 8

Plateau::Plateau()
{
	this->_graph = {};
	this->_currentEclosionCount = 0;
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
	const auto cityName = utils::menu::chooseCity(
		std::cout,
		std::cin,
		this->_graph.getCityNames()
	);
	auto& city = this->_graph.getCity(cityName);

	for (int i = 3 - city.cubesDe(city.couleur); i > 0; --i)
		utils::cities::addBlock(city, city);
}

void Plateau::actionInfecter()
{
	std::cout << "Veuillez choisir une ville à infecter:" << std::endl;
	const auto cityName = utils::menu::chooseCity(
		std::cout,
		std::cin,
		this->_graph.getCityNames()
	);
	auto& city = this->_graph.getCity(cityName);

	if (city.totalCubes() >= 3)
	{
		std::cout << city.nom << " est deja a 3 cubes total -> ECLOSION!" << std::endl;
		this->_currentEclosionCount = utils::cities::solveEclosion(
			this->_graph,
			city,
			this->_currentEclosionCount
		);
	}
	else
		utils::cities::addBlock(city, city);
	
}

void Plateau::actionPlacerRail()
{
	if (this->_graph.getRailsCount() >= MAX_RAIL_COUNT)
	{
		std::cout << "La limite de " << MAX_RAIL_COUNT << " rails a déjà été atteinte." << std::endl;
		return;
	}

	std::cout << "Veuillez choisir une ville où placer un rail:" << std::endl;
	const auto startCity = utils::menu::chooseCity(
		std::cout,
		std::cin,
		this->_graph.getCityNames()
	);

	std::cout << std::endl;
	std::cout << "Veuillez choisir où le rail se termine:" << std::endl;
	const auto endCity = utils::menu::chooseCity(
		std::cout,
		std::cin,
		this->_graph.getNeighbors(startCity, ROAD)
	);

	if (this->_graph.getAvailableTransportModes(startCity, endCity) & TRAIN)
	{
		std::cout << "Un rail existe déjà entre '" << startCity << "' et '" << endCity << "'." << std::endl;
		return;
	}

	this->_graph.addRail(startCity, endCity);
}

void Plateau::actionPlusCourtChemin()
{
	auto cities = this->_graph.getCityNames();

	std::cout << "Veuillez choisir une ville de départ:" << std::endl;
	const auto startCity = utils::menu::chooseCity(
		std::cout,
		std::cin,
		cities
	);

	cities.erase(startCity);

	std::cout << std::endl;
	std::cout << "Veuillez choisir une destination:" << std::endl;
	const auto endCity = utils::menu::chooseCity(
		std::cout,
		std::cin,
		cities
	);

	std::cout << "=== " << startCity << " -> " << endCity << " ===" << std::endl;

	// === ROAD ===
	const auto roadPath = utils::pathfinding::BFS(
		this->_graph,
		startCity,
		endCity,
		ROAD
	);
	const auto roadActionCount = roadPath.size() - 1;

	std::cout << "[ROUTE] Terrestre uniquement (" << roadActionCount << " actions):" << std::endl;
	utils::menu::displayPath(std::cout, roadPath, this->_graph);

	// === ROAD + TRAIN ===
	const auto roadAndRailsPath = utils::pathfinding::BFS(
		this->_graph,
		startCity,
		endCity,
		ROAD | TRAIN
	);
	const auto roadAndRailsActionCount = roadAndRailsPath.size() - 1;

	std::cout << std::endl;
	std::cout << "[ROUTE + TRAIN] Terrestre + Rails (" << roadAndRailsActionCount << " actions):" << std::endl;
	utils::menu::displayPath(std::cout, roadAndRailsPath, this->_graph);
	std::cout << "=> Gain de " + std::to_string(roadActionCount - roadAndRailsActionCount) <<
		" action(s) grâce aux rails!" << std::endl;

	// === ALL ===
	const auto roadAndRailsAndBoatsPath = utils::pathfinding::BFS(
		this->_graph,
		startCity,
		endCity,
		ROAD | TRAIN | BOAT
	);
	const auto roadAndRailsAndBoatsActionCount = roadAndRailsAndBoatsPath.size() - 1;

	std::cout << std::endl;
	std::cout << "[TOUT] Terrestre + Rails + Mer (" << roadAndRailsAndBoatsActionCount << " actions):" << std::endl;
	utils::menu::displayPath(std::cout, roadAndRailsAndBoatsPath, this->_graph);
	std::cout << "=> Gain de " + std::to_string(roadActionCount - roadAndRailsAndBoatsActionCount) <<
		" action(s) grâce au total!" << std::endl;
}

void Plateau::afficherEtat()
{
	std::cout << "=== Etat du Plateau ===" << std::endl;
	std::cout << "Eclosion : " << this->_currentEclosionCount << " / " << MAX_ECLOSION_COUNT << std::endl;
	std::cout << "Rails    : " << this->_graph.getRailsCount() << " / " << MAX_RAIL_COUNT << std::endl;

	for (auto cityName : this->_graph.getCityNames())
	{
		const auto city = this->_graph.getCity(cityName);

		if (city.totalCubes() == 0)
			continue;
		
		std::cout << city.nom << ":";

		for (const auto color : city.cubes | std::views::keys)
			std::cout << " " << utils::cities::getColorName(color) << " x" << city.cubesDe(color);
		
		std::cout << std::endl;
	}
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
		if (this->_currentEclosionCount >= MAX_ECLOSION_COUNT)
		{
			std::cout << "Partie perdue!" << std::endl;
			return;
		}

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
