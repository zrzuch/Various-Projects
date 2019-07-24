/*
  FileName    : Frustum.h
  Author      : Zachary Zuch
  Description : Calculates Frustum Plane Equations and checks if a Sphere is within the frustum.
*/
#pragma once

#include <vector>
#include <string>
#include "Vector3.h"
#include "Matrix4.h"

/* Sources -
	http://www.txutxi.com/?p=444
	http://www.lighthouse3d.com/tutorials/view-frustum-culling/
*/

// Sphere BV
struct SphereBV
{
	SphereBV();

	~SphereBV() = default;

	Vector3 center;
	float radius;
};

// Axis Aligned Box
struct BoxBV
{
	BoxBV();

	void
	init(const std::vector<float>& lrbtnf);

	Vector3&
	operator[] (unsigned n);

	Vector3 points[8];
	static constexpr unsigned NUM_POINTS = 8;
};

struct Plane
{
	Plane();

	// Plane Equation
	// Ax + By + Cz + D = 0
	// where (A, B, C) is the normal vector
	Plane(float A, float B, float C, float D);

	void
	normalize();

	float
	dist(Vector3& point);

	Vector3
	pointIntersection(Vector3& point, Vector3& direction);

	void
	printPlaneInfo(const std::string& planeName) const;

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
