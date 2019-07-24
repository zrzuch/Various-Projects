/*
  FileName    : Camera.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 3
  Description : This file is the camera source file which has the 
  				implementation for the camera.
*/

#include <cmath>
#include "Camera.h"
#include "Math.h"
#include <iostream>

Camera::Camera ()
	: m_updateView		(true)
	, m_updateProjection(true)
	, m_currProjection	(ProjectionType::SYMMETRIC)
	, m_fov				(50.0f)
	, m_beginFov		(m_fov)
	, m_aspectRatio		(4.0f/3.0f)
	, m_nearZ			(0.1f)
	, m_farZ			(120.0f) // Large since the current model is very large
	, m_world 			(0,10,24)
	, m_beginWorld		(m_world)
{ }

void
Camera::reset()
{
	m_world = m_beginWorld;
	if (m_currProjection == ProjectionType::SYMMETRIC)
	{
		m_fov = m_beginFov;
		m_updateProjection = true;
	}
	m_updateView = true;
}

// Move "distance" units along the right vector
void
Camera::moveRight ( float distance )
{
	m_world.moveRight(distance);
	m_updateView = true;
}

// Move "distance" units along the up vector
void
Camera::moveUp    ( float distance )
{
	m_world.moveUp(distance);
	m_updateView = true;
}

// Move "distance" units along the back vector
void
Camera::moveBack  ( float distance )
{
	m_world.moveBack(distance);
	m_updateView = true;
}

void
Camera::pitch ( float degrees )
{
	m_world.pitch(degrees);
	m_updateView = true;
}

void
Camera::yaw ( float degrees )
{
	m_world.yaw(degrees);
	m_updateView = true;
}

void
Camera::roll ( float degrees )
{
	m_world.roll(degrees);
	m_updateView = true;
}

void
Camera::setPosition (float x, float y, float z)
{
	m_world.setPosition(x, y, z);
	m_beginWorld.setPosition(x, y, z);
	m_updateView = true;
}

// Set the position of the camera
void
Camera::setPosition ( const Vector3& position )
{
	m_world.setPosition(position);
	m_beginWorld.setPosition(position);
	m_updateView = true;
}

/*
Sets the unit vectors so that the interface provides support
	to have the camera have the desired orientation
*/
void
Camera::setUnitVectors (const Transform& world)
{
	m_world = world;
	m_world.orthonormalize();
	m_beginWorld = m_world;
	m_updateView = true;
}

// Align local Y with world Y. Adjust other basis vectors
//   so they are orthonormal. 
void
Camera::alignWithWorldY ()
{
	m_world.alignWithWorldY();
	m_updateView = true;
}

Matrix3
Camera::getEyeMatrix() const
{
	return m_world.getOrientation();
}

// Return the view matrix, only recomputing it if necessary
// You can use this matrix as the model-view matrix
Transform
Camera::getViewMatrix () const
{
	if ( m_updateView )
	{
		m_modelView = m_world;
		m_modelView.invertRt();
		m_updateView = false;
	}
	return m_modelView;
}

// Decrement the field of view (FOV) by "verticalFovDelta".
// Clamp the FOV to the range [ 1, 120 ] degrees. 
void
Camera::zoom (float verticalFovDelta)
{
	if (m_currProjection == ProjectionType::SYMMETRIC)
	{
		m_fov = Math::clamp(m_fov - verticalFovDelta, 1.0f, 120.0f);
		m_updateProjection = true;
	}
}

void
Camera::setAspectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	if (m_currProjection == ProjectionType::SYMMETRIC)
	{
		m_updateProjection = true;
	}
}

void
Camera::setProjection()
{
	m_updateProjection = true;
    m_currProjection = ProjectionType::SYMMETRIC;
}

void
Camera::setProjection(float verticalFovDegrees)
{
	m_fov = verticalFovDegrees;
	m_beginFov = m_fov;

	m_updateProjection = true;
    m_currProjection = ProjectionType::SYMMETRIC;
}

// Set the camera to use a symmetric perspective projection.
// NOTE we are now using double-s, which should be reflected
//   in relevant data members.
// For all projection methods, farZ > nearZ > 0. 
void
Camera::setProjection (float verticalFovDegrees, float aspectRatio,
               float nearZ, float farZ)
{
	m_fov = verticalFovDegrees;
	m_beginFov = m_fov;

	m_aspectRatio = aspectRatio;
	m_nearZ = nearZ;
	m_farZ = farZ;

    m_updateProjection = true;
    m_currProjection = ProjectionType::SYMMETRIC;
}

// Set the camera to use an asymmetric perspective projection.
void
Camera::setProjection (double left, double right, double bottom, double top,
               double nearZ, double farZ)
{
	m_left = left;
	m_right = right;

	m_bottom = bottom;
	m_top = top;
	m_nearZ = nearZ;
	m_farZ = farZ;

	m_updateProjection = true;
	m_currProjection = ProjectionType::ASYMMETRIC;
}

// Set the camera to use an orthographic projection.
void
Camera::setOrthoProjection (double left, double right, double bottom, double top,
                    double nearZ, double farZ)
{
	m_left = left;
	m_right = right;

	m_bottom = bottom;
	m_top = top;
	m_nearZ = nearZ;
	m_farZ = farZ;

	m_updateProjection = true;
	m_currProjection = ProjectionType::ORTHOGRAPHIC;
}

// Return the projection matrix, only recomputing it if necessary
Matrix4
Camera::getProjectionMatrix () const
{
	if (m_updateProjection)
	{
		if (m_currProjection == ProjectionType::SYMMETRIC)
		{
			m_projection.setToPerspectiveProjection(m_fov, m_aspectRatio, 
				m_nearZ, m_farZ);
		} 
		else if (m_currProjection == ProjectionType::ASYMMETRIC)
		{
			m_projection.setToPerspectiveProjection(m_left, m_right, m_bottom, 
				m_top, m_nearZ, m_farZ);
		}
		else
		{
			m_projection.setToOrthographicProjection(m_left, m_right, m_bottom, 
				m_top, m_nearZ, m_farZ);
		}
		m_updateProjection = false;
	}
	return m_projection;
}

float
Camera::getXFOV() const
{
	return getYFOV() * m_aspectRatio;
}

float
Camera::getYFOV() const
{
	if (m_currProjection == ProjectionType::SYMMETRIC)
	{
		return m_fov;
	}
	else
	{
		return Math::toDegrees(atan(m_top/m_nearZ));
	}
}