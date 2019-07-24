#include "Frustum.h"

/****************************************************************************************/
// SphereBV Class

SphereBV::SphereBV()
: center()
, radius()
{ }

/****************************************************************************************/
// BoxBV Class

BoxBV::BoxBV()
: points(NUM_POINTS)
{ }

void
BoxBV::init(std::vector<float>& lrbtnf)
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

void
BoxBV::init(std::vector<float>& lrbtnf, const Matrix3& rotation)
{
	Vector3 point = 
	{
		lrbtnf[0], lrbtnf[2], lrbtnf[4]
	};
	point = rotation * point;
	points[0] = point;

	point = 
	{
		lrbtnf[0], lrbtnf[2], lrbtnf[5]
	};
	point = rotation * point;
	points[1] = point;

	point = 
	{
		lrbtnf[0], lrbtnf[3], lrbtnf[4]
	};
	point = rotation * point;
	points[2] = point;

	point = 
	{
		lrbtnf[0], lrbtnf[3], lrbtnf[5]
	};
	point = rotation * point;
	points[3] = point;

	point = 
	{
		lrbtnf[1], lrbtnf[2], lrbtnf[4]
	};
	point = rotation * point;
	points[4] = point;

	point = 
	{
		lrbtnf[1], lrbtnf[2], lrbtnf[5]
	};
	point = rotation * point;
	points[5] = point;

	point = 
	{
		lrbtnf[1], lrbtnf[3], lrbtnf[4]
	};
	point = rotation * point;
	points[6] = point;
	
	point = 
	{
		lrbtnf[1], lrbtnf[3], lrbtnf[5]
	};
	point = rotation * point;
	points[7] = point;
}

Vector3&
BoxBV::operator[] (unsigned n)
{
	return points[n];
}

/****************************************************************************************/
// Plane Class

Plane::Plane() 
{ }

// Plane Equation
// Ax + By + Cz + D = 0
// where (A, B, C) is the normal vector
Plane::Plane(float A, float B, float C, float D)
: normal(A, B, C)
, d(D)
{ }

void
Plane::normalize()
{
	float l = normal.length();
	normal /= l;
	d /= l;
}

float
Plane::dist(Vector3& point)
{
	return normal.dot(point) + d;
}

void
Plane::printPlaneInfo(const std::string& planeName) const
{
	std::cout << planeName << " : " << normal.x << "x + " << normal.y << "y + " << normal.z << "z + " << d << " = 0" << std::endl;
}

/****************************************************************************************/
// Frustum Class

Frustum::Frustum(const Matrix4& MVP)
: fPlanes(NUM_PLANES)
{
	init(MVP);

	//printFrustumInfo();
}

void
Frustum::init(const Matrix4& MVP)
{
	fPlanes[ LEFT 	] = 
	{
		MVP.m_right.x + MVP.m_translation.x, 
		MVP.m_right.y + MVP.m_translation.y, 
		MVP.m_right.z + MVP.m_translation.z,
		MVP.m_right.w + MVP.m_translation.w
	};
	fPlanes[ LEFT 	].normalize();

	fPlanes[ RIGHT 	] = 
	{
		-MVP.m_right.x + MVP.m_translation.x, 
		-MVP.m_right.y + MVP.m_translation.y, 
		-MVP.m_right.z + MVP.m_translation.z,
		-MVP.m_right.w + MVP.m_translation.w
	};
	fPlanes[ RIGHT 	].normalize();

	fPlanes[ BOTTOM ] = 
	{
		MVP.m_up.x + MVP.m_translation.x, 
		MVP.m_up.y + MVP.m_translation.y, 
		MVP.m_up.z + MVP.m_translation.z,
		MVP.m_up.w + MVP.m_translation.w
	};
	fPlanes[ BOTTOM ].normalize();

	fPlanes[ TOP  	] = 
	{
		-MVP.m_up.x + MVP.m_translation.x, 
		-MVP.m_up.y + MVP.m_translation.y, 
		-MVP.m_up.z + MVP.m_translation.z,
		-MVP.m_up.w + MVP.m_translation.w
	};
	fPlanes[ TOP 	].normalize();

	fPlanes[ NEAR 	] = 
	{
		MVP.m_back.x + MVP.m_translation.x, 
		MVP.m_back.y + MVP.m_translation.y, 
		MVP.m_back.z + MVP.m_translation.z,
		MVP.m_back.w + MVP.m_translation.w
	};
	fPlanes[ NEAR 	].normalize();

	fPlanes[ FAR 	] = 
	{
		-MVP.m_back.x + MVP.m_translation.x, 
		-MVP.m_back.y + MVP.m_translation.y, 
		-MVP.m_back.z + MVP.m_translation.z,
		-MVP.m_back.w + MVP.m_translation.w
	};
	fPlanes[ FAR 	].normalize();
}

// The normal is facing perpendicular outside of the Frustum
bool
Frustum::inFrustum(SphereBV& sphere)
{
	for (unsigned i = 0; i < NUM_PLANES; ++i)
	{
		float distance = fPlanes[i].dist(sphere.center);
		if (distance < -sphere.radius)
		{
			// OUTSIDE
			return false;
		}
	}
	// EITHER INSIDE or INTERSECT
	return true;
}

bool
Frustum::inFrustum(BoxBV& box)
{
	for (unsigned i = 0; i < NUM_PLANES; ++i)
	{
		unsigned outsideCount = 0;
		for (unsigned j = 0; j < box.NUM_POINTS; ++j)
		{
			float distance = fPlanes[i].dist(box.points[j]);
			if (distance < 0)
			{
				++outsideCount;
			}
		}
		if (outsideCount == box.NUM_POINTS)
		{
			return false;
		}
	}
	return true;
}

void
Frustum::printFrustumInfo() const
{
	fPlanes[ LEFT 	].printPlaneInfo("Left");
	fPlanes[ RIGHT 	].printPlaneInfo("Right");
	fPlanes[ BOTTOM ].printPlaneInfo("Bottom");
	fPlanes[ TOP  	].printPlaneInfo("Top");
	fPlanes[ NEAR 	].printPlaneInfo("Near");
	fPlanes[ FAR 	].printPlaneInfo("Far");
}

/*
	Notes:
		- Bounding Volumes could be improved if distance was calculated, so objects far off screen just need to use Sphere calculations
		while those closer can have more complex algorithms
		- Add additional case to axis-aligned boxes that allow for additional checking if some points are out
*/