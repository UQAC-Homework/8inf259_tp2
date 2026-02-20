#include "../include/Map.h"
#include "../include/Set.h"
#include "../include/Ville.h"

#include <stdexcept>
#include <utility>

template <typename T, typename U>
Map<T, U>::Map()
{
	this->_internal = std::map<T, U>();
}

template <typename T, typename U>
Map<T, U>::~Map() = default;

template <typename T, typename U>
const U& Map<T, U>::at(const T& key) const
{
	if (!this->contains(key))
		throw std::out_of_range("Key was not found");

	return this->_internal.at(key);
}

template <typename T, typename U>
void Map<T, U>::insert(const T& key, const U& value)
{
	this->_internal[key] = std::move(value);
}

template <typename T, typename U>
void Map<T, U>::erase(const T& key)
{
	this->_internal.erase(key);
}

template <typename T, typename U>
void Map<T, U>::clear()
{
	this->_internal.clear();
}

template <typename T, typename U>
bool Map<T, U>::contains(const T& key) const
{
	return this->_internal.contains(key);
}

template <typename T, typename U>
size_t Map<T, U>::size() const
{
	return this->_internal.size();
}

template <typename T, typename U>
U& Map<T, U>::operator[](const T& key)
{
	if (!this->contains(key))
		throw std::out_of_range("Key was not found");

	return this->_internal[key];
}

template class Map<std::string, int>;
template class Map<int, Set<int>>;
template class Map<int, Ville>;
