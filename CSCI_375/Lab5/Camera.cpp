/*
  FileName    : Camera.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 3
  Description : This file is the camera source file which has the 
  				implementation for the camera.
*/

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

#include "Camera.h"

Camera::Camera ()
	: m_updateModelView( true )
	, m_position ( 0, 0, 12.0f ), m_beginPosition ( m_position )
	, m_local(), m_beginLocal( m_local )
{
	setProjection(50.0f, 1200.0f / 900, 0.01f, 40.0f);
}

Camera::~Camera ()
{ }

void
Camera::reset()
{
	m_position = m_beginPosition;
	m_local = m_beginLocal;
	m_updateModelView = true;
}

// Move "distance" units along the right vector
void
Camera::moveRight ( float distance )
{
	m_position += distance * m_local.getRight();
	m_updateModelView = true;
}

// Move "distance" units along the up vector
void
Camera::moveUp    ( float distance )
{
	m_position += distance * m_local.getUp();
	m_updateModelView = true;
}

// Move "distance" units along the back vector
void
Camera::moveBack  ( float distance )
{
	m_position += distance * m_local.getBack();
	m_updateModelView = true;
}

void
Camera::pitch ( float degrees )
{
	Matrix3 rotateX;
	rotateX.setToRotationX(degrees);
	m_local = rotateX * m_local;
	m_updateModelView = true;
}

void
Camera::yaw ( float degrees )
{
	Matrix3 rotateY;
	rotateY.setToRotationY(degrees);
	m_local = rotateY * m_local;
	m_updateModelView = true;
}

void
Camera::roll ( float degrees )
{
	Matrix3 rotateZ;
	rotateZ.setToRotationZ(degrees);
	m_local = rotateZ * m_local;
	m_updateModelView = true;
}

// Set the position of the camera
void
Camera::setPosition ( const Vector3& position )
{
	m_position = position;
	m_beginPosition = position;
	m_updateModelView = true;
}

/*
Sets the unit vectors so that the interface provides support
	to have the camera have the desired orientation
*/
void
Camera::setUnitVectors (Matrix3& local)
{
	m_local = local;
	m_local.orthonormalize();
	m_beginLocal = m_local;

	m_updateModelView = true;
}

// Return the view matrix, only recomputing it if necessary
// You can use this matrix as the model-view matrix
glm::mat4
Camera::getViewMatrix () const
{
	if ( m_updateModelView )
	{
		m_modelView = glm::lookAt((glm::vec3)m_position, 
			(glm::vec3)(m_position - m_local.getBack()), 
			(glm::vec3)m_local.getUp());
		m_updateModelView = false;
	}
	return m_modelView;
}

// Set the projection parameters
void
Camera::setProjection (float verticalFovDegrees, float aspectRatio,
               float nearZ, float farZ)
{
	m_verticalFovDegrees = verticalFovDegrees;
	m_aspectRatio = aspectRatio;
	m_nearZ = nearZ;
	m_farZ = farZ;

	m_projection = glm::perspective( glm::radians( m_verticalFovDegrees ), 
			m_aspectRatio, m_nearZ, m_farZ );
}

// Return the projection matrix, only recomputing it if necessary
glm::mat4
Camera::getProjectionMatrix () const
{
	return m_projection;
}