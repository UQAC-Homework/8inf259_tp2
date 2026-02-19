#include "../include/Map.h"

#include <stdexcept>

template <typename T, typename U>
Map<T, U>::Map()
{
	this->_internal = std::map<T, U>();
}

template <typename T, typename U>
Map<T, U>::~Map() = default;

template <typename T, typename U>
void Map<T, U>::set(T key, U value)
{
	this->_internal[key] = value;
}

template <typename T, typename U>
U Map<T, U>::get(T key)
{
	if (!this->contains(key))
		throw std::out_of_range("Key was not found");

	return this->_internal[key];
}

template <typename T, typename U>
bool Map<T, U>::contains(T key)
{
	return this->_internal.contains(key);
}
