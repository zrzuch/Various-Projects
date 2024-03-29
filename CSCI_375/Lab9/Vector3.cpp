#include <cmath>
#include <iomanip>
#include <iostream>
#include <glm/vec3.hpp>

#include "Vector3.h"
#include "Math.h"

// Initialize to zero vector
Vector3::Vector3 ()
	: x(0), y(0), z(0)
{ }

// Initialize each component with "xyz"
Vector3::Vector3 (float xyz)
	: x( xyz ), y( xyz ), z( xyz )
{ }

// Initialize with corresponding parameter
Vector3::Vector3 (float x, float y, float z)
	: x( x ), y( y ), z( z )
{ }

// Assign each data member "xyz"
void
Vector3::set (float xyz)
{
	x = xyz;
	y = xyz;
	z = xyz;
}

// Assign each data member from corresponding parameter
void
Vector3::set (float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

// Negate this
void
Vector3::negate ()
{
	x *= -1.0f;
	y *= -1.0f;
	z *= -1.0f;
}

const float*
Vector3::data () const
{
  return &x;
}

// Compute this dot "v"
float
Vector3::dot (const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

// Return angle b/w this and "v"
float
Vector3::angleBetween (const Vector3& v) const
{
	return Math::toDegrees( acos( dot(v) / ( length() * v.length())));
}

Vector3
Vector3::interpolate(Vector3 end, float progression)
{
	float newX = x + (end.x - x) * progression;
	float newY = y + (end.y - y) * progression;
	float newZ = z + (end.z - z) * progression;
	return Vector3(newX, newY, newZ);
}

// Compute this cross "v"
Vector3
Vector3::cross (const Vector3& v) const
{
	return Vector3( 
		y * v.z - z * v.y, 
		z * v.x - x * v.z, 
		x * v.y - y * v.x 
	);
}

// Compute length of this
float
Vector3::length () const
{
	return sqrt( dot( *this ));
}

// Normalize this
void
Vector3::normalize ()
{
	(*this) /= length();
}

Vector3::operator glm::vec3() const
{
	return glm::vec3(x, y, z);
}

Vector3&
Vector3::operator+= (const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

Vector3&
Vector3::operator-= (const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

Vector3&
Vector3::operator*= (float s)
{
	x *= s;
	y *= s;
	z *= s;

	return *this;
}

Vector3&
Vector3::operator/= (float s)
{
	x /= s;
	y /= s;
	z /= s;

	return *this;
}

Vector3
operator+ (const Vector3& v1, const Vector3& v2)
{
	Vector3 vec(v1);
	return vec += v2;
}

Vector3
operator- (const Vector3& v)
{
	Vector3 vec(v);
	vec.negate();
	return vec;
}

Vector3
operator- (const Vector3& v1, const Vector3& v2)
{
	Vector3 vec(v1);
	return vec -= v2;
}

Vector3
operator* (float s, const Vector3& v)
{
	Vector3 vec(v);
	return vec *= s;
}

Vector3
operator* (const Vector3& v, float s)
{
	Vector3 vec(v);
	return vec *= s;
}

Vector3
operator/ (const Vector3& v, float s)
{
	Vector3 vec(v);
	return vec /= s;
}

float
dot (const Vector3& v, float x, float y, float z)
{
	return v.x * x + v.y * y + v.z * z;
}

std::ostream&
operator<< (std::ostream& out, const Vector3& v)
{
	std::ios_base::fmtflags origState = out.flags();
	out << std::setprecision(2) << "[ " 
		<< std::setw(10) << v.x 
		<< std::setw(10) << v.y 
		<< std::setw(10) << v.z << " ]";
	out.flags( origState );
	return out;
}