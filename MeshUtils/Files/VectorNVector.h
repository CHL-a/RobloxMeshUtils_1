#ifndef VECTORNVECTOR_H
#define VECTORNVECTOR_H

#include "PointerVector.h"
#include "VectorN.h"

template<typename T>
class VectorNVector: public PointerVector<T> {
	static_assert(
		std::is_base_of<VectorN, T>::value,
		"T must be derived from VectorN"
	);
	public: 
		VectorNVector();
		VectorNVector(
			std::vector<T*> &referral, 
			bool should_dereference=false
		);
		VectorNVector(const uint32_t &size);

		int find(const T *needle, int i=0)const override;
};

#include "VectorNVector.tpp"

#endif