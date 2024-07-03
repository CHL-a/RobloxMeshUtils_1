#include "VectorN.h"
#include <cmath>

using namespace std;

// ############################################################
// VectorN
// ############################################################

bool VectorN::fuzzy_equal(
	const VectorN &other, 
	const double &epsilon) const{
	return abs(_x - other._x) <= epsilon && 
		abs(_y - other._y) <= epsilon;
}

float VectorN::x()const{return _x;}
void VectorN::x(float &alt){_x = alt;}
float VectorN::y()const{return _y;}
void VectorN::y(float &alt){_y = alt;}

// ############################################################
// Vector2
// ############################################################

// CONSTRUCTORS
Vector2::Vector2(float x, float y) {_x = x;_y = y;};

// OPERATIONS
ostream& operator<<(ostream& os1, const Vector2&self) {
	return os1 << "Vector2(" 
		<< self.x() 
		<< ',' 
		<< self.x() 
		<< ')';
};

bool operator==(const Vector2 &left, const Vector2 &right){
	return left.fuzzy_equal(right, 0);
};

bool operator!=(const Vector2 &left, const Vector2 &right){
	return !(left == right);
};

// Other
Vector2 Vector2::yAxis = Vector2(0,1);

// ############################################################
// Vector3
// ############################################################

using namespace std;

// CONSTRUCTORS
Vector3::Vector3(float x, float y, float z) {_x=x;_y=y;_z=z;};

Vector3::Vector3(const Vector3 &self):
	Vector3(self._x, self._y, self._z){};

// METHODS
float Vector3::z()const{return this->_z;};
void Vector3::z(float &z){_z=z;};

double Vector3::get_magnitude()const{
	return sqrt(_x*_x + _y*_y + _z*_z);
}

Vector3 Vector3::get_unit()const{
	return *this / this->get_magnitude();
}

Vector3 Vector3::cross(const Vector3 &other)const{
	return Vector3(
		_y*other._z - other._y*_z,
		-(_x*other._z - other._x*_z),
		_x*other._y - other._x*_y
	);
};

bool Vector3::fuzzy_equal(
	const VectorN &other, 
	const double &epsilon) const {
	
	const Vector3* alt = dynamic_cast<const Vector3*>(&other);
	return alt && 
		this->VectorN::fuzzy_equal(other, epsilon) && 
		abs(_z - alt->_z) <= epsilon;

};

// OPERATIONS
Vector3 Vector3::operator+(const Vector3 &other)const{
	return Vector3(_x+other._x,_y+other._y,_z+other._z);
};

Vector3 Vector3::operator-()const{return Vector3(-_x,-_y,-_z);};

Vector3 Vector3::operator-(const Vector3 &other) const{
	return Vector3(_x-other._x,_y-other._y,_z-other._z);
};

Vector3 Vector3::operator*(const Vector3 &other) const{
	return Vector3(_x*other._x,_y*other._y,_z*other._z);
};

Vector3 Vector3::operator*(const double &other) const{
	return Vector3(_x*other,_y*other,_z*other);
};

Vector3 Vector3::operator/(const Vector3 &other) const {
	return Vector3(_x/other._x,_y/other._y,_z/other._z);
};

Vector3 Vector3::operator/(const double &other) const {
	return Vector3(_x/other,_y/other,_z/other);
};

Vector3& Vector3::operator=(const Vector3 &other){
	if (this == &other) return *this;

	_x = other._x;
	_y = other._y;
	_z = other._z;

	return *this;
};

ostream& operator<<(ostream& os1, const Vector3 &self) {
	return os1 << "Vector3(" 
		<< self.x() 
		<< ',' 
		<< self.y() 
		<< ','
		<< self.z()
		<< ')';
};

bool operator==(const Vector3 &left, const Vector3 &right){
	return left.fuzzy_equal(right, 0);
};

bool operator!=(const Vector3 &left, const Vector3 &right){
	return !(left == right);
};
