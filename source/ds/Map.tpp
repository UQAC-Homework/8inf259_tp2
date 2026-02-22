#pragma once

#include <utility>

#include "../../include/exceptions/KeyNotFoundException.h"

namespace ds
{
	template <typename Key, typename Value>
	Map<Key, Value>::Map()
	{
		this->_internal = std::map<Key, Value>();
	}

	template <typename Key, typename Value>
	Map<Key, Value>::~Map() = default;

	template <typename Key, typename Value>
	size_t Map<Key, Value>::size() const
	{
		return this->_internal.size();
	}

	template <typename Key, typename Value>
	Value& Map<Key, Value>::operator[](const Key& key)
	{
		if (!this->contains(key))
			throw exceptions::KeyNotFoundException(key);

		return this->_internal[key];
	}

	template <typename Key, typename Value>
	const Value& Map<Key, Value>::at(const Key& key) const
	{
		if (!this->contains(key))
			throw exceptions::KeyNotFoundException(key);

		return this->_internal.at(key);
	}

	template <typename Key, typename Value>
	void Map<Key, Value>::insert(const Key& key, const Value& value)
	{
		this->_internal[key] = std::move(value);
	}

	template <typename Key, typename Value>
	void Map<Key, Value>::erase(const Key& key)
	{
		this->_internal.erase(key);
	}

	template <typename Key, typename Value>
	void Map<Key, Value>::clear()
	{
		this->_internal.clear();
	}

	template <typename Key, typename Value>
	bool Map<Key, Value>::contains(const Key& key) const
	{
		return this->_internal.contains(key);
	}

	template <typename Key, typename Value>
	Map<Key, Value>::const_iterator Map<Key, Value>::begin() const
	{
		return this->_internal.begin();
	}

	template <typename Key, typename Value>
	Map<Key, Value>::const_iterator Map<Key, Value>::end() const
	{
		return this->_internal.end();
	}
}
