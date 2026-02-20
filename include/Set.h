#ifndef INC_8INF259_TP2_SET_H
#define INC_8INF259_TP2_SET_H
#include <cstddef>
#include <set>

template <typename T>
class Set
{
	std::set<T> _internal;

public:
	Set();
	~Set();

	/// Gets the size of this collection
	[[nodiscard]] std::size_t size() const;

	/// Inserts the value into this collection
	void insert(const T& value);

	/// Erases the value from this collection
	void erase(const T& value);

	/// Clears every element of this collection
	void clear();

	/// Checks if this collection contains the given value
	[[nodiscard]] bool contains(const T& value) const;
};


#endif //INC_8INF259_TP2_SET_H
