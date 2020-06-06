#include "MyVec.hpp"
#include "math.h"

//////////////////////////////////
////////// CONSTRUCTORS //////////
//////////////////////////////////

/**
 * Desc: Empty constructor, creates a zero vector.
 */
my_vec::my_vec2::my_vec2()
{
  _x = 0.0;
  _y = 0.0;
}


/**
 * Desc: Constructor with the components.
 *
 * @x_ : x-component.
 * @y_ : y-component.
 */
my_vec::my_vec2::my_vec2( const double x_, const double y_ )
{
  _x = x_;
  _y = y_;
}



//////////////////////////////////////
////////// GETTERS, SETTERS //////////
//////////////////////////////////////
/**
 * Desc: Returns the x-component.
 *
 * return : x-component.
 */
double my_vec::my_vec2::x() const
{
  return _x;
}


/**
 * Desc: Returns the y-component.
 *
 * return : y-component.
 */
double my_vec::my_vec2::y() const
{
  return _y;
}


/**
 * Desc: Sets x-component.
 *
 * @x_ : x-component.
 */
void my_vec::my_vec2::set_x( const double x_ )
{
  _x = x_;
}


/**
 * Desc: Sets y-component.
 *
 * @y_ : y-component.
 */
void my_vec::my_vec2::set_y( const double y_ )
{
  _y = y_;
}


/**
 * Desc: Sets vector components.
 *
 * @x_ : new x-component.
 * @y_ : new y-component.
 */
void my_vec::my_vec2::set( const double x_, const double y_ )
{
  _x = x_;
  _y = y_;
}



/////////////////////////////////////
////////// BASIC OPERATORS //////////
/////////////////////////////////////
/**
 * Desc: Assignment operator.
 *
 * @vector_ : vector to be equal to.
 * return : 
 */
my_vec::my_vec2& my_vec::my_vec2::operator=( const my_vec2 &vector_ )
{
  _x = vector_._x;
  _y = vector_._y;

  return *this;
}


/**
 * Desc: Compound addition operator.
 *
 * @vector_ : addition vector.
 * return : increased vector.
 */
my_vec::my_vec2& my_vec::my_vec2::operator+=( const my_vec2 &vector_ )
{
  _x += vector_._x;
  _y += vector_._y;

  return *this;
}


/**
 * Desc: Binary addition operator.
 *
 * @vector_ : addition vector.
 * return : increased vector.
 */
const my_vec::my_vec2 my_vec::my_vec2::operator+( const my_vec2 &vector_ ) const
{
  my_vec2 result = *this;
  result += vector_;

  return result;
}


/**
 * Desc: Compound subtraction operator.
 *
 * @vector_ : subtracted vector.
 * return : decreased vector.
 */
my_vec::my_vec2& my_vec::my_vec2::operator-=( const my_vec2 &vector_ )
{
  _x -= vector_._x;
  _y -= vector_._y;

  return *this;
}


/**
 * Desc: Binary subtraction operator.
 *
 * @vector_ : subtracted vector.
 * return : decreased vector.
 */
const my_vec::my_vec2 my_vec::my_vec2::operator-( const my_vec2 &vector_ ) const
{
  my_vec2 result = *this;
  result -= vector_;

  return result;
}


/**
 * Desc: Scalar product.
 *
 * @vector_ : vector to multiply with.
 * return : scalar product of the vectors.
 */
const double my_vec::my_vec2::operator*( const my_vec2 &vector_ ) const
{
  return _x*vector_._x + _y*vector_._y;
}


/**
 * Compound scalar multiplication operator.
 *
 * @scalar_ : multiplier.
 * return : increased vector.
 */
my_vec::my_vec2& my_vec::my_vec2::operator*=( const double scalar_ )
{
  _x *= scalar_;
  _y *= scalar_;

  return *this;
}


/**
 * Desc: Binary subtraction operator.
 *
 * @vector_ : subtracted vector.
 * return : increased vector.
 */
const my_vec::my_vec2 my_vec::my_vec2::operator*( const double scalar_ ) const
{
  my_vec2 result = *this;
  result *= scalar_;

  return result;
}


/**
 * Desc: Compound scalar division operator.
 *
 * @scalar_ : divider.
 * return : decreased vector.
 */
my_vec::my_vec2& my_vec::my_vec2::operator/=( const double scalar_ )
{
  _x /= scalar_;
  _y /= scalar_;

  return *this;
}


/**
 * Desc: Binary division operator.
 *
 * @vector_ : divider vector.
 * return : decreased vector.
 */
const my_vec::my_vec2 my_vec::my_vec2::operator/( const double scalar_ ) const
{
  my_vec2 result = *this;
  result /= scalar_;

  return result;
}

//////////////////////////////////////
////////// OTHER OPERATIONS //////////
//////////////////////////////////////

/**
 * Desc: Returns the length of the vector.
 *
 * return : length of the vector.
 */
const double my_vec::my_vec2::length() const
{
  return sqrt( _x*_x + _y*_y );
}


/**
 * Desc: Sets length of the vector.
 *
 * @length_ : new length.
 */
void my_vec::my_vec2::set_length( const double length_ )
{
  double a = atan2( _y, _x );
  set( length_*cos(a), length_*sin(a) );
}


/**
 * Desc: Returns the argument of the vector.
 *
 * return : angle between the vector and the x-axis.
 */
const double my_vec::my_vec2::angle() const
{
  return atan2( _y, _x );
}


/**
 * Desc: Sets argument of the vector.
 *
 * @angle_ : new argument.
 */
void my_vec::my_vec2::set_angle( const double angle_ )
{
  double l = length();
  set( l*cos(angle_), l*sin(angle_) );
}


/**
 * Desc: Normalizes vector length to unit.
 */
void my_vec::my_vec2::normalize()
{
  set_length( 1.0 );
}


/**
 * Desc: Rotates the vector by a given angle (in radian).
 *
 * @angle_ : angle of rotation in radian.
 */
void my_vec::my_vec2::rotate( const double angle_ )
{
  double a = angle();
  set_angle( a + angle_ );  
}


/**
 * Desc: Empty constructor, creates a zero vector.
 */
my_vec::my_vec3::my_vec3()
{
	_x = 0.0;
	_y = 0.0;
	_z = 0.0;

}


/**
 * Desc: Constructor with the components.
 *
 * @x_ : x-component.
 * @y_ : y-component.
 * @z_ : z-component.
 */
my_vec::my_vec3::my_vec3(const double x_, const double y_, const double z_)
{
	_x = x_;
	_y = y_;
	_z = z_;

}



//////////////////////////////////////
////////// GETTERS, SETTERS //////////
//////////////////////////////////////
/**
 * Desc: Returns the x-component.
 *
 * return : x-component.
 */
double my_vec::my_vec3::x() const
{
	return _x;
}


/**
 * Desc: Returns the y-component.
 *
 * return : y-component.
 */
double my_vec::my_vec3::y() const
{
	return _y;
}

/**
 * Desc: Returns the z-component.
 *
 * return : z-component.
 */
double my_vec::my_vec3::z() const
{
	return _z;
}

/**
 * Desc: Sets x-component.
 *
 * @x_ : x-component.
 */
void my_vec::my_vec3::set_x(const double x_)
{
	_x = x_;
}


/**
 * Desc: Sets y-component.
 *
 * @y_ : y-component.
 */
void my_vec::my_vec3::set_y(const double y_)
{
	_y = y_;
}

/**
 * Desc: Sets z-component.
 *
 * @z_ : z-component.
 */
void my_vec::my_vec3::set_z(const double z_)
{
	_z = z_;
}


/**
 * Desc: Sets vector components.
 *
 * @x_ : new x-component.
 * @y_ : new y-component.
 * @z_ : new z-component.
 */
void my_vec::my_vec3::set(const double x_, const double y_, const double z_)
{
	_x = x_;
	_y = y_;
	_z = z_;

}



/////////////////////////////////////
////////// BASIC OPERATORS //////////
/////////////////////////////////////
/**
 * Desc: Assignment operator.
 *
 * @vector_ : vector to be equal to.
 * return :
 */
my_vec::my_vec3& my_vec::my_vec3::operator=(const my_vec3 &vector_)
{
	_x = vector_._x;
	_y = vector_._y;
	_z = vector_._z;
	return *this;
}


/**
 * Desc: Compound addition operator.
 *
 * @vector_ : addition vector.
 * return : increased vector.
 */
my_vec::my_vec3& my_vec::my_vec3::operator+=(const my_vec3 &vector_)
{
	_x += vector_._x;
	_y += vector_._y;
	_z += vector_._z;
	return *this;
}


/**
 * Desc: Binary addition operator.
 *
 * @vector_ : addition vector.
 * return : increased vector.
 */
const my_vec::my_vec3 my_vec::my_vec3::operator+(const my_vec3 &vector_) const
{
	my_vec3 result = *this;
	result += vector_;

	return result;
}


/**
 * Desc: Compound subtraction operator.
 *
 * @vector_ : subtracted vector.
 * return : decreased vector.
 */
my_vec::my_vec3& my_vec::my_vec3::operator-=(const my_vec3 &vector_)
{
	_x -= vector_._x;
	_y -= vector_._y;
	_z -= vector_._z;

	return *this;
}


/**
 * Desc: Binary subtraction operator.
 *
 * @vector_ : subtracted vector.
 * return : decreased vector.
 */
const my_vec::my_vec3 my_vec::my_vec3::operator-(const my_vec3 &vector_) const
{
	my_vec3 result = *this;
	result -= vector_;

	return result;
}


/**
 * Desc: Scalar product.
 *
 * @vector_ : vector to multiply with.
 * return : scalar product of the vectors.
 */
const double my_vec::my_vec3::operator*(const my_vec3 &vector_) const
{
	return _x * vector_._x + _y * vector_._y + _z * vector_._z;
}


/**
 * Compound scalar multiplication operator.
 *
 * @scalar_ : multiplier.
 * return : increased vector.
 */
my_vec::my_vec3& my_vec::my_vec3::operator*=(const double scalar_)
{
	_x *= scalar_;
	_y *= scalar_;
	_z *= scalar_;

	return *this;
}


/**
 * Desc: Binary subtraction operator.
 *
 * @vector_ : subtracted vector.
 * return : increased vector.
 */
const my_vec::my_vec3 my_vec::my_vec3::operator*(const double scalar_) const
{
	my_vec3 result = *this;
	result *= scalar_;

	return result;
}


/**
 * Desc: Compound scalar division operator.
 *
 * @scalar_ : divider.
 * return : decreased vector.
 */
my_vec::my_vec3& my_vec::my_vec3::operator/=(const double scalar_)
{
	_x /= scalar_;
	_y /= scalar_;
	_z /= scalar_;

	return *this;
}


/**
 * Desc: Binary division operator.
 *
 * @vector_ : divider vector.
 * return : decreased vector.
 */
const my_vec::my_vec3 my_vec::my_vec3::operator/(const double scalar_) const
{
	my_vec3 result = *this;
	result /= scalar_;

	return result;
}

//////////////////////////////////////
////////// OTHER OPERATIONS //////////
//////////////////////////////////////

/**
 * Desc: Returns the length of the vector.
 *
 * return : length of the vector.
 */
const double my_vec::my_vec3::length() const
{
	return sqrt(_x*_x + _y * _y+ _z * _z);
}


