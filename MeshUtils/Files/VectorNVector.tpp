#include "VectorNVector.h"

template<typename T>
VectorNVector<T>::VectorNVector(): 
	PointerVector<T>(){};

template<typename T>
VectorNVector<T>::VectorNVector(
	std::vector<T*> &referral, 
	bool should_dereference
	): 
	PointerVector<T>(referral, should_dereference){};

template<typename T>
VectorNVector<T>::VectorNVector(const uint32_t &size):
	PointerVector<T>(size){};

template<typename T>
int VectorNVector<T>::find(const T *needle, int i)const{
	const uint32_t n = this->size();

	for (; i < n; i++)
		if (this->at(i)->fuzzy_equal(*needle)) 
			return i;

	return -1;
};