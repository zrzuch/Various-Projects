/*
  FileName    : Camera.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 3
  Description : This file is the camera header file which has the interface
  				for the camera.
*/

#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <glm/vec3.hpp>

class Vector3
{

public:

	Vector3 ();

	Vector3 (float xyz);

	Vector3 (float x, float y, float z);

	void
	set (float xyz);

	void
	set (float x, float y, float z);

	void
	negate ();

	const float*
  	data () const;

  	float*
	data ();

	float
	dot (const Vector3& v) const;

	float
	angleBetween (const Vector3& v) const;

	Vector3
	interpolate(Vector3 end, float progression);

	Vector3
	cross (const Vector3& v) const;

	float
	length () const;

	void
	abs();

	void
	normalize ();

	Vector3
	linearInterpolation(Vector3 vec2, Vector3 scale);

	operator glm::vec3() const;

	float&
	operator[] (int n);

	const float&
	operator[] (int n) const;

	Vector3&
	operator+= (const Vector3& v);

	Vector3&
	operator-= (const Vector3& v);

	Vector3&
	operator*= (float s);

	Vector3&
	operator/= (float s);

	Vector3&
	operator/= (const Vector3& vec);

	float x;
	float y;
	float z;
};

// Free operators declared outside class
Vector3
operator+ (const Vector3& v1, const Vector3& v2);

Vector3
operator- (const Vector3& v1, const Vector3& v2);

Vector3
operator- (const Vector3& v);

Vector3
operator* (float s, const Vector3& v);

Vector3
operator* (const Vector3& v, float s);

Vector3
operator/ (const Vector3& v, float s);

float
dot (const Vector3& v, float x, float y, float z);

std::ostream&
operator<< (std::ostream& out, const Vector3& v);

#endif