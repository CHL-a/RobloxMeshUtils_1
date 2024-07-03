#include "Color3a.h"

// CONSTUCTORS
Color3a::Color3a(
	const uint8_t &r0,
	const uint8_t &g0,
	const uint8_t &b0,
	const uint8_t &a0
	){
	r(r0);
	g(g0);
	b(b0);
	a(a0);
};

// METHODS
uint8_t Color3a::r()const{return _r;};
void Color3a::r(const uint8_t &v){_r=v;};
uint8_t Color3a::g()const{return _g;};
void Color3a::g(const uint8_t &v){_g=v;};
uint8_t Color3a::b()const{return _b;};
void Color3a::b(const uint8_t &v){_b=v;};
uint8_t Color3a::a()const{return _a;};
void Color3a::a(const uint8_t &v){_a=v;};
		
// STATICS
Color3a Color3a::default_c3a = Color3a();

Color3a* Color3a::get_default(){
	return &default_c3a;
};