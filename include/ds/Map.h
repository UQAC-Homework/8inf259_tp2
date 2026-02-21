#ifndef INC_8INF259_TP2_MAP_H
#define INC_8INF259_TP2_MAP_H
#include <map>

namespace ds
{
	template <typename Key, typename Value>
	class Map
	{
		std::map<Key, Value> _internal;

	public:
		Map();
		~Map();

		/// Gets the amount of elements in the collection
		[[nodiscard]] std::size_t size() const;

		/// Gets the value at the given key
		Value& operator[](const Key& key);

		/// Gets the value at the given key
		[[nodiscard]] const Value& at(const Key& key) const;

		/// Inserts the given value at the given key
		void insert(const Key& key, const Value& value);

		/// Erases the value at the given key
		void erase(const Key& key);

		/// Clears every element of the collection
		void clear();

		/// Checks if the given key is present
		[[nodiscard]] bool contains(const Key& key) const;

		using iterator = std::map<Key, Value>::iterator;
		using const_iterator = std::map<Key, Value>::const_iterator;

		const_iterator begin() const;
		const_iterator end() const;
	};
}

#include "../../source/ds/Map.tpp"

#endif //INC_8INF259_TP2_MAP_H
