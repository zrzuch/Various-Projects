#include "Frustum.h"

Frustum::Frustum(const Matrix4& MVP)
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