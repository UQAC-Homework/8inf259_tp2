#ifdef _WIN32
#include <windows.h>
#endif
#include "include/Plateau.h"

int main(const int argc, char* argv[])
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif
	
	std::string file = "../board.txt";

	if (argc > 1)
		file = argv[1];

	Plateau plateau;

	if (!plateau.charger(file))
		return 1;

	plateau.menu();
	return 0;
}
