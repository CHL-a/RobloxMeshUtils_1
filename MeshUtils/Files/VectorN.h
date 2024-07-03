#ifndef VECTORN_H
#define VECTORN_H

// ########################################################
// VectorN
// ########################################################

class VectorN {
	protected:
		float _x, 
			_y;

	public:
		virtual bool fuzzy_equal(
			const VectorN &other, 
			const double &epsilon = 1E-6
		) const;
		virtual float x()const;
		virtual void x(float &alt);
		virtual float y()const;
		virtual void y(float &alt);
};

// ########################################################
// Vector2
// ########################################################

#include <iostream>

class Vector2: public VectorN {
	public:
		static Vector2 yAxis;

		Vector2(float x = 0, float y = 0);
};

std::ostream& operator<<(std::ostream& os1, const Vector2 &self);
bool operator==(const Vector2 &left, const Vector2 &right);
bool operator!=(const Vector2 &left, const Vector2 &right);

// ########################################################
// Vector3
// ########################################################

class Vector3: public VectorN {
	protected:
		float _z;
	
	public:
		Vector3(const Vector3 &self);
		Vector3(float x = 0, float y = 0, float z = 0);

		float z()const;
		void z(float &other);
		double get_magnitude()const;
		Vector3 get_unit()const;
		Vector3 cross(const Vector3 &other)const;

		Vector3 operator+(const Vector3 &other) const;
		Vector3 operator-()const;
		Vector3 operator-(const Vector3 &other) const;
		Vector3 operator*(const Vector3 &other) const;
		Vector3 operator*(const double &other) const;
		Vector3 operator/(const Vector3 &other) const;
		Vector3 operator/(const double &other) const;
		Vector3& operator=(const Vector3 &other);
		bool fuzzy_equal(
			const VectorN &other, 
			const double &epsilon = 1E-6
		) const override;
};

std::ostream& operator<<(std::ostream& os1, const Vector3 &self);

bool operator==(const Vector3 &left, const Vector3 &right);
bool operator!=(const Vector3 &left, const Vector3 &right);


#endif