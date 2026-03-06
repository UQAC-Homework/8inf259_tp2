#include "../include/TransportMode.h"

TransportMode operator|(const TransportMode mode1, const TransportMode mode2)
{
	const unsigned char num_mode1 = mode1;
	const unsigned char num_mode2 = mode2;

	return static_cast<TransportMode>(num_mode1 | num_mode2);
}
