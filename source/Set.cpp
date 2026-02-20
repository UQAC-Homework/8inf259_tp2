#include "../include/Set.h"

template <typename T>
Set<T>::Set() = default;

template <typename T>
Set<T>::~Set() = default;

template <typename T>
std::size_t Set<T>::size() const
{
	return this->_internal.size();
}

template <typename T>
void Set<T>::insert(const T& value)
{
	this->_internal.insert(value);
}

template <typename T>
void Set<T>::erase(const T& value)
{
	this->_internal.erase(value);
}

template <typename T>
void Set<T>::clear()
{
	this->_internal.clear();
}

template <typename T>
bool Set<T>::contains(const T& value) const
{
	return this->_internal.contains(value);
}

template class Set<int>;
