#ifdef _WIN32
#include <windows.h>
#endif
#include "include/Plateau.h"

int main(const int argc, char* argv[]) {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif

	std::string file = "board.txt";
	
	if (argc > 1)
		file = argv[1];
	
	Plateau plateau;
	
	if (!plateau.charger(file))
		return 1;
	
	plateau.menu();
	return 0;
}
// ============================================================
// Code du menu (à intégrer dans votre Plateau.cpp)
// ============================================================
//
// void Plateau::menu() {
// while (true) {
// std::cout << "\n";
// std::cout << "+======================================+" << std::endl;
// std::cout << "| PANDEMIC IBERIA -- MENU |" << std::endl;
// std::cout << "+======================================+" << std::endl;
// std::cout << "| 1. Placer 3 cubes sur une ville |" << std::endl;
// std::cout << "| 2. Infecter une ville (+1 cube) |" << std::endl;
// std::cout << "| 3. Placer un rail |" << std::endl;
// std::cout << "| 4. Plus court chemin |" << std::endl;
// std::cout << "| 5. Afficher l'etat du plateau |" << std::endl;
// std::cout << "| 0. Quitter |" << std::endl;
// std::cout << "+======================================+" << std::endl;
// std::cout << "> Choix : ";
//
// int choix;
// if (!(std::cin >> choix)) {
// std::cin.clear();
// std::cin.ignore(INT_MAX, '\n');
// continue;
// }
//
// switch (choix) {
// case 1: actionPlacerTroisCubes(); break;
// case 2: actionInfecter(); break;
// case 3: actionPlacerRail(); break;
// case 4: actionPlusCourtChemin(); break;
// case 5: afficherEtat(); break;
// case 0:
// std::cout << "Au revoir !" << std::endl;
// return;
// default:
// std::cout << "Choix invalide." << std::endl;
// }
// }
// }