#include "../include/TransportMode.h"

TransportMode operator|(const TransportMode mode1, const TransportMode mode2)
{
	const unsigned char numMode1 = mode1;
	const unsigned char numMode2 = mode2;

	return static_cast<TransportMode>(numMode1 | numMode2);
}
