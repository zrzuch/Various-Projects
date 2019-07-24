#include <cmath>
#include <iostream>
#include <iomanip>

#include "Vector4.h"

// Initialize to zero vector.
Vector4::Vector4 ()
: x(0), y(0), z(0), w(0)
{ }

// Initialize each component from "xyzw". 
Vector4::Vector4 (float xyzw)
: x(xyzw), y(xyzw), z(xyzw), w(xyzw)
{ }

// Initialize with corresponding parameter. 
Vector4::Vector4 (float x, float y, float z, float w)
: x(x), y(y), z(z), w(w)
{ }

// Return a const pointer to the first element. 
const float*
Vector4::data () const
{
  return &x;
}

// Assign each data member "xyzw". 
void
Vector4::set (float xyzw)
{
  x = xyzw;
  y = xyzw;
  z = xyzw; 
  w = xyzw;
}

// Assign each data member from corresponding parameter. 
void
Vector4::set (float x, float y, float z, float w)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

// Compute this dot "v". 
float
Vector4::dot (const Vector4& v) const
{
  return x * v.x + y * v.y + z * v.z + w * v.w;
}

float
Vector4::dot (float x, float y, float z, float w) const
{
  return this->x * x + this->y * y + this->z * z + this->w * w;
}

// Compute length of this. 
float
Vector4::length () const
{
  return sqrt(dot(*this));
}

// Normalize this. 
void
Vector4::normalize ()
{
  (*this) /= length();
}

// Negate this. 
void
Vector4::negate ()
{
  x = -x;
  y = -y;
  z = -z;
  w = -w;
}

// Operators
Vector4&
Vector4::operator+= (const Vector4& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  w += v.w;

  return *this;
}

Vector4&
Vector4::operator-= (const Vector4& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  w -= v.w;

  return *this;
}

Vector4&
Vector4::operator*= (const Vector4& v)
{
  x *= v.x;
  y *= v.y;
  z *= v.z;
  w *= v.w;

  return *this;
}

Vector4&
Vector4::operator*= (float scalar)
{
  x *= scalar;
  y *= scalar;
  z *= scalar;
  w *= scalar;

  return *this;
}

Vector4&
Vector4::operator/= (float scalar)
{
  x /= scalar;
  y /= scalar;
  z /= scalar;
  w /= scalar;

  return *this;
}

  
// These free operators MUST call the corresponding member functions. 
Vector4
operator+ (const Vector4& v1, const Vector4& v2)
{
  Vector4 vec(v1);
  return vec += v2;
}

Vector4
operator- (const Vector4& v1, const Vector4& v2)
{
  Vector4 vec(v1);
  return vec -= v2;
}

// Unary negation. Calls member "negate". 
Vector4
operator- (const Vector4& v)
{
  Vector4 vec(v);
  vec.negate();
  return vec;
}

Vector4
operator* (const Vector4& v1, const Vector4& v2)
{
  Vector4 vec(v1);
  return vec *= v2;
}

Vector4
operator* (const Vector4& v, float scalar)
{
  Vector4 vec(v);
  return vec *= scalar;
}

Vector4
operator* (float scalar, const Vector4& v)
{
  Vector4 vec(v);
  return vec *= scalar;
}

Vector4
operator/ (const Vector4& v, float scalar)
{
  Vector4 vec(v);
  return vec /= scalar;
}

// Output "v" using TWO digits of precision and a
//   field width of 10 for each component. 
std::ostream&
operator<< (std::ostream& out, const Vector4& v)
{
  std::ios_base::fmtflags origState = out.flags();
  out << std::setprecision(2) << "[ " 
    << std::setw(10) << v.x 
    << std::setw(10) << v.y 
    << std::setw(10) << v.z 
    << std::setw(10) << v.w << " ]";
  out.flags( origState );
  return out;
}
