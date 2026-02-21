#ifndef INC_8INF259_TP2_SET_H
#define INC_8INF259_TP2_SET_H
#include <cstddef>
#include <set>

namespace ds
{
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

		using iterator = std::set<T>::iterator;
		using const_iterator = std::set<T>::const_iterator;

		const_iterator begin() const;
		const_iterator end() const;
	};
}

#include "../../source/ds/Set.tpp"

#endif //INC_8INF259_TP2_SET_H
