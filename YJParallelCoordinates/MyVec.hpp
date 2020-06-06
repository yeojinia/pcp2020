#ifndef MY_VEC_H
#define MY_VEC_H

#include <vector>

namespace my_vec {

  class my_vec2 {
  private:
    double _x;
    double _y;

  public:
    // Constructors
    my_vec2();
    my_vec2( const double x_, const double y_ );

    // Setters and getters
    double x() const;
    double y() const;
    void set_x( const double x_ );
    void set_y( const double y_ );
    void set( const double x_, const double y_ );

    // Basic operators
    // vector-vector
    my_vec2& operator =( const my_vec2 &vector_ );
    my_vec2& operator +=( const my_vec2 &vector_ );
    const my_vec2 operator +( const my_vec2 &vector_ ) const;
    my_vec2& operator -=( const my_vec2 &vector_ );
    const my_vec2 operator -( const my_vec2 &vector_ ) const;
    const double operator *( const my_vec2 &vector_ ) const;
    // vector-scalar
    my_vec2& operator *=( const double scalar_ );
    const my_vec2 operator *( const double scalar_ ) const;
    my_vec2& operator /=( const double scalar_ );
    const my_vec2 operator /( const double scalar_ ) const;

    // Other operations
    const double length() const;
    const double angle() const;
    void set_length( const double length_ );
    void set_angle( const double angle_ );

    void normalize();
    void rotate( const double angle_ );
  };

  class my_vec3 {
  private:
	  double _x;
	  double _y;
	  double _z;
  public:
	  // Constructors
	  my_vec3();
	  my_vec3(const double x_, const double y_, double z_);

	  // Setters and getters
	  double x() const;
	  double y() const;
	  double z() const;
	  void set_x(const double x_);
	  void set_y(const double y_);
	  void set_z(const double z_);
	  void set(const double x_, const double y_, const double z_);

	  // Basic operators
	  // vector-vector
	  my_vec3& operator =(const my_vec3 &vector_);
	  my_vec3& operator +=(const my_vec3 &vector_);
	  const my_vec3 operator +(const my_vec3 &vector_) const;
	  my_vec3& operator -=(const my_vec3 &vector_);
	  const my_vec3 operator -(const my_vec3 &vector_) const;
	  const double operator *(const my_vec3 &vector_) const;
	  // vector-scalar
	  my_vec3& operator *=(const double scalar_);
	  const my_vec3 operator *(const double scalar_) const;
	  my_vec3& operator /=(const double scalar_);
	  const my_vec3 operator /(const double scalar_) const;

	  const double length() const;
	};
 
}


#endif // MY_VEC_H
