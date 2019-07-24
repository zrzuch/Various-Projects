/*
  FileName    : Camera.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 3
  Description : This file is the camera source file which has the 
  				implementation for the camera.
*/

#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Math.h"

Camera::Camera ()
	: m_updateModelView( true )
	, m_world(0,0,12), m_beginWorld( m_world )
{
	setProjection(50.0f, 1200.0f / 900, 0.01f, 40.0f);
}

void
Camera::reset()
{
	m_world = m_beginWorld;
	m_updateModelView = true;
}

// Move "distance" units along the right vector
void
Camera::moveRight ( float distance )
{
	m_world.moveRight(distance);
	m_updateModelView = true;
}

// Move "distance" units along the up vector
void
Camera::moveUp    ( float distance )
{
	m_world.moveUp(distance);
	m_updateModelView = true;
}

// Move "distance" units along the back vector
void
Camera::moveBack  ( float distance )
{
	m_world.moveBack(distance);
	m_updateModelView = true;
}

void
Camera::pitch ( float degrees )
{
	m_world.pitch(degrees);
	m_updateModelView = true;
}

void
Camera::yaw ( float degrees )
{
	m_world.yaw(degrees);
	m_updateModelView = true;
}

void
Camera::roll ( float degrees )
{
	m_world.roll(degrees);
	m_updateModelView = true;
}

void
Camera::setPosition (float x, float y, float z)
{
	m_world.setPosition(x, y, z);
	m_beginWorld.setPosition(x, y, z);
	m_updateModelView = true;
}

// Set the position of the camera
void
Camera::setPosition ( const Vector3& position )
{
	m_world.setPosition(position);
	m_beginWorld.setPosition(position);
	m_updateModelView = true;
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
	m_updateModelView = true;
}

// Align local Y with world Y. Adjust other basis vectors
//   so they are orthonormal. 
void
Camera::alignWithWorldY ()
{
	m_world.alignWithWorldY();
	m_updateModelView = true;
}

// Return the view matrix, only recomputing it if necessary
// You can use this matrix as the model-view matrix
Transform
Camera::getViewMatrix () const
{
	if ( m_updateModelView )
	{
		m_modelView = m_world;
		m_modelView.invertRt();
		m_updateModelView = false;
	}
	return m_modelView;
}

// Set the projection parameters
void
Camera::setProjection (float verticalFovDegrees, float aspectRatio,
               float nearZ, float farZ)
{
	m_projection = glm::perspective( Math::toRadians( verticalFovDegrees ), 
			aspectRatio, nearZ, farZ );
}

// Return the projection matrix, only recomputing it if necessary
glm::mat4
Camera::getProjectionMatrix () const
{
	return m_projection;
}