/*
  FileName    : Frustum.h
  Author      : Zachary Zuch
  Description : Calculates Frustum Plane Equations and checks if a Sphere is within the frustum.
*/
#pragma once

#include "Matrix4.h"
#include "Vector3.h"
#include <vector>
#include <string>

/* Sources -
	http://www.txutxi.com/?p=444
	http://www.lighthouse3d.com/tutorials/view-frustum-culling/
*/

// Sphere BV
struct SphereBV
{
	SphereBV()
	: center()
	, radius()
	{ }
	
	Vector3 center;
	float radius;
};

// Axis Aligned Box
struct BoxBV
{	
	BoxBV() { }

	void
	init(const std::vector<float>& lrbtnf)
	{
		points[0] = Vector3(lrbtnf[0], lrbtnf[2], lrbtnf[4]);
		points[1] = Vector3(lrbtnf[0], lrbtnf[2], lrbtnf[5]);
		points[2] = Vector3(lrbtnf[0], lrbtnf[3], lrbtnf[4]);
		points[3] = Vector3(lrbtnf[0], lrbtnf[3], lrbtnf[5]);
		points[4] = Vector3(lrbtnf[1], lrbtnf[2], lrbtnf[4]);
		points[5] = Vector3(lrbtnf[1], lrbtnf[2], lrbtnf[5]);
		points[6] = Vector3(lrbtnf[1], lrbtnf[3], lrbtnf[4]);
		points[7] = Vector3(lrbtnf[1], lrbtnf[3], lrbtnf[5]);
	}

	Vector3&
	operator[] (unsigned n)
	{
		return points[n];
	}

	Vector3 points[8];
	static constexpr unsigned NUM_POINTS = 8;
};

struct Plane
{
	Plane() { }

	// Plane Equation
	// Ax + By + Cz + D = 0
	// where (A, B, C) is the normal vector
	Plane(float A, float B, float C, float D)
	: normal(A, B, C)
	, d(D)
	{ }

	void
	normalize()
	{
		float l = normal.length();
		normal /= l;
		d /= l;
	}

	float
	dist(Vector3& point)
	{
		return normal.dot(point) + d;
	}

	void
	printPlaneInfo(const std::string& planeName) const
	{
		std::cout << planeName << " : " << normal.x << "x + " << normal.y << "y + " << normal.z << "z + " << d << " = 0" << std::endl;
	}

	Vector3 normal;
	float d;
};

class Frustum
{
public:

	Frustum(const Matrix4& MVP);

	void
	init(const Matrix4& MVP);

	bool
	inFrustum(SphereBV& sphere);

	bool
	inFrustum(BoxBV& box);

	void
	printFrustumInfo() const;

private:

	Plane fPlanes[6];

	static constexpr unsigned LEFT 			= 0;
	static constexpr unsigned RIGHT 		= 1;
	static constexpr unsigned BOTTOM 		= 2;
	static constexpr unsigned TOP 			= 3;
	static constexpr unsigned NEAR 			= 4;
	static constexpr unsigned FAR 			= 5;

	static constexpr unsigned NUM_PLANES 	= 6;
};
