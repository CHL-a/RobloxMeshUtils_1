#ifndef COLOR3A_H
#define COLOR3A_H

#include <cstdint>

class Color3a{
	protected:
		uint8_t _r, _g, _b, _a;
		static Color3a default_c3a;

	public:
		Color3a(
			const uint8_t &r0 = 0xFF,
			const uint8_t &g0 = 0xFF,
			const uint8_t &b0 = 0xFF,
			const uint8_t &a0 = 0
		);

		static Color3a* get_default();

		uint8_t r()const;
		void r(const uint8_t &v);
		uint8_t g()const;
		void g(const uint8_t &v);
		uint8_t b()const;
		void b(const uint8_t &v);
		uint8_t a()const;
		void a(const uint8_t &v);
};

#endif