#include "BOSWrapper.h"


using namespace std;

// CONSTRUCTORS
BOSWrapper::BOSWrapper(std::ostream *v){
	value = v;
};

// DESTRUCTORS
BOSWrapper::~BOSWrapper(){value = nullptr;};

// METHODS
/**
 * Explicit append for characters
 */
BOSWrapper* BOSWrapper::append_c(const uint8_t &c){
	value->put(c);
	return this;
};

/**
 * Explicit append for floats
 */
BOSWrapper* BOSWrapper::append_f(const float &f){
	return this->append(f);
};

BOSWrapper* BOSWrapper::append(const string &c){
	value->write(c.c_str(), c.size());
	return this;
};

template <typename T>
BOSWrapper* BOSWrapper::append(const T &p){

	static_assert(std::is_arithmetic<T>::value, "T must be a primitive type");
	value->write(reinterpret_cast<const char*>(&p), sizeof(T));
	return this;
};