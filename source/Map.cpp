#include "../include/Map.h"

#include <set>

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
void Map<T, U>::set(T key, U value)
{
	this->_internal[key] = std::move(value);
}

template <typename T, typename U>
U& Map<T, U>::at(const T& key)
{
	if (!this->contains(key))
		throw std::out_of_range("Key was not found");

	return this->_internal.at(key);
}

template <typename T, typename U>
const U& Map<T, U>::at(const T& key) const
{
	if (!this->contains(key))
		throw std::out_of_range("Key was not found");

	return this->_internal.at(key);
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
std::vector<T> Map<T, U>::keys() const
{
	std::vector<T> values;
	values.reserve(this->_internal.size());

	for (const auto& [key, value] : this->_internal)
		values.emplace_back(key);

	return values;
}

// TODO: Evaluate if replacing this by an iterator is useful
template <typename T, typename U>
std::vector<U> Map<T, U>::values() const
{
	std::vector<U> values;
	values.reserve(this->_internal.size());

	for (const auto& [key, value] : this->_internal)
		values.emplace_back(value);

	return values;
}

template class Map<std::string, int>;
template class Map<int, std::set<int>>;
template class Map<int, Ville>;
