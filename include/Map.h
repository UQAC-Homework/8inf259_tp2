#ifndef INC_8INF259_TP2_MAP_H
#define INC_8INF259_TP2_MAP_H
#include <map>
#include <vector>

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
	[[nodiscard]] U& at(const T& key);
	
	/// Gets the value at the given key
	[[nodiscard]] const U& at(const T& key) const;

	/// Checks if the given key is present
	[[nodiscard]] bool contains(const T& key) const;

	/// Gets the amount of keys
	[[nodiscard]] std::size_t size() const;

	/// Gets the values stored in the collection
	[[nodiscard]] std::vector<U> values() const;
};

#endif //INC_8INF259_TP2_MAP_H
