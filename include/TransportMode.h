#ifndef INC_8INF259_TP2_TRANSPORTMODE_H
#define INC_8INF259_TP2_TRANSPORTMODE_H

/// Every transport mode available
enum TransportMode : unsigned char
{
	NONE = 0,
	ROAD = 1,
	TRAIN = 1 << 1,
	BOAT = 1 << 2,
	ALL = ROAD | TRAIN | BOAT
};

/// Gets the combination of the modes
TransportMode operator|(TransportMode mode1, TransportMode mode2);

#endif //INC_8INF259_TP2_TRANSPORTMODE_H
