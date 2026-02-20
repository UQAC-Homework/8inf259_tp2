#ifndef INC_8INF259_TP2_MAP_H
#define INC_8INF259_TP2_MAP_H
#include <map>

template <typename T, typename U>
class Map
{
	std::map<T, U> _internal;

public:
	Map();
	~Map();

	/// Sets the given value at the given key
	void set(T key, U value);

	/// Gets the value at the given key
	[[nodiscard]] U& at(T key);

	/// Checks if the given key is present
	[[nodiscard]] bool contains(T key) const;
};

#endif //INC_8INF259_TP2_MAP_H
