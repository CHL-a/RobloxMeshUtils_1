#ifndef BOSWRAPPER_H
#define BOSWRAPPER_H

#include <iostream>
#include <cstdint>

class BOSWrapper {
	protected:
		std::ostream *value;

	public:
		BOSWrapper(std::ostream *v);
		
		~BOSWrapper();

		BOSWrapper* append_c(const uint8_t &c);
		BOSWrapper* append_f(const float &f);
		BOSWrapper* append(const std::string &s);

		template <typename T>
		BOSWrapper* append(const T &p);
};

#include "BOSWrapper.tpp"

#endif