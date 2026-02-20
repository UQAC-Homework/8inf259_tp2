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

	/// Gets the amount of elements in the collection
	[[nodiscard]] std::size_t size() const;

	/// Gets the value at the given key
	U& operator[](const T& key);

	/// Gets the value at the given key
	[[nodiscard]] const U& at(const T& key) const;

	/// Inserts the given value at the given key
	void insert(const T& key, const U& value);

	/// Erases the value at the given key
	void erase(const T& key);

	/// Clears every element of the collection
	void clear();

	/// Checks if the given key is present
	[[nodiscard]] bool contains(const T& key) const;
};

#endif //INC_8INF259_TP2_MAP_H
