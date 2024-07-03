#include "PointerVector.h"

using namespace std;

// CONSTRUCTORS
template <typename T>
PointerVector<T>::PointerVector() {};

template <typename T>
PointerVector<T>::PointerVector(
	vector<T*> &referral,
	bool should_dereference){
	const uint32_t n = referral.size();

	this->resize(n);

	for (uint32_t i = 0; i < n; i++) {
		this->at(i) = referral.at(i);
		
		if (should_dereference)
			referral.at(i) = nullptr;
		
	}
};

template <typename T>
PointerVector<T>::PointerVector(const uint32_t &size){
	this->resize(size);
};

// METHODS
/**
 * Simple finding function, if i is not used, 0 will be used 
 * instead, it denotes the start of the search.
 */
template <typename T>
int PointerVector<T>::find(const T *needle, int i)const{
	const uint32_t n = this->size();

	for (; i < n; i++){
		T* p = this->at(i);

		if (*needle == *p) 
			return i;
	}

	return -1;
};

/**
 * Removes all nullptrs by swapping non nulls and nulls, 
 * causing them to populate at the left side then resizing
*/
template <typename T>
void PointerVector<T>::remove_nulls(){
	uint32_t availible_p = 0,
		p = 0;
	const uint32_t n = this->size();

	// swap all nulls with non nulls
	for (; availible_p < n; availible_p++) {
		T* p_value = this->at(availible_p);

		if (p_value != nullptr) continue;
		if (p == 0) p = availible_p + 1;
		
		for (; p < n; p++) {
			p_value = this->at(p);

			if (p_value == nullptr) continue;
			
			break;
		}

		if (p_value == nullptr) break;
		
		this->at(availible_p) = p_value;
		this->at(p) = nullptr;
	}

	// resize
	this->resize(availible_p);
};

/**
 * Replaces all pointers not in set (via indices) with null
 */
template <typename T>
void PointerVector<T>::intersection_i(std::set<uint32_t> &other){
	const uint32_t n = this->size();
	const set<uint32_t>::iterator end = other.end();

	for (uint32_t i = 0; i < n; i++) {
		if (other.find(i) == end) {
			this->at(i) = nullptr;
		}
	}
};