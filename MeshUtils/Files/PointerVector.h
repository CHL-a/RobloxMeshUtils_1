#ifndef POINTERVECTOR_H
#define POINTERVECTOR_H

#include <vector>
#include <set>
#include <cstdint>

/**
 * Attempts to extend vector with extra methods
 */
template <typename T>
class PointerVector: public std::vector<T*> {
	public:
		PointerVector();
		PointerVector(
			std::vector<T*> &referral, 
			bool should_dereference=false);
		PointerVector(const uint32_t &size);

		virtual int find(const T *needle, int start=0)const;
		void remove_nulls();
		void intersection_i(std::set<uint32_t> &other);
};

#include "PointerVector.tpp"

#endif