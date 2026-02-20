#include "../include/Map.h"
#include "../include/Graph.h"
#include "../include/Ville.h"

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
U& Map<T, U>::at(T key)
{
	if (!this->contains(key))
		throw std::out_of_range("Key was not found");

	return this->_internal.at(key);
}

template <typename T, typename U>
bool Map<T, U>::contains(T key) const
{
	return this->_internal.contains(key);
}

template class Map<std::string, Ville>;
template class Map<std::string, std::vector<std::string>>;
template class Map<std::string_view, Graph::Node*>;
