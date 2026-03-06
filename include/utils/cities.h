#ifndef INC_8INF259_TP2_CITIES_H
#define INC_8INF259_TP2_CITIES_H
#include "../Ville.h"

namespace utils::cities
{
	/// Adds a block from the given city to the given city
	inline void addBlock(const Ville& source, Ville& target)
	{
		const std::string color = source.couleur;
		
		if (!target.cubes.contains(color))
			target.cubes.insert({color, 0});
		
		target.cubes[color]++;
	}
}

#endif //INC_8INF259_TP2_CITIES_H