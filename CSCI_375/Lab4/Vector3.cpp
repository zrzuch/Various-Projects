#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

#include "Vector3.h"

// Initialize to zero vector
Vector3::Vector3 ()
	: x(), y(), z()
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
	return glm::degrees( glm::acos( dot(v) / ( length() * v.length())));
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
