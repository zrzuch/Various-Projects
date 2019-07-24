/*
  FileName    : Camera.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 3
  Description : This file is the camera source file which has the 
  				implementation for the camera.
*/

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

Camera::Camera ()
	: m_projection_needs_update (true)
	, m_pitch ( 0 ), m_begin_pitch ( 0 )
	, m_yaw ( 0 ), m_begin_yaw ( 0 )
	, m_roll ( 0 ), m_begin_roll ( 0 )
	, m_position ( 0, 0, 12.0f ), m_begin_position ( 0, 0, 12.0f )
	, m_verticalFovDegrees (50.0f), m_aspectRatio (1200.0f / 900)
	, m_nearZ (0.01f), m_farZ (40.0f)
{
	calculateUnitVectors();
}

Camera::~Camera ()
{ }

void
Camera::reset()
{
	m_position = m_begin_position;
	m_pitch = m_begin_pitch;
	m_yaw = m_begin_yaw;
	m_roll = m_begin_roll;

	calculateUnitVectors();
}

// Move "distance" units along the right vector
void
Camera::moveRight ( float distance )
{
	m_position += distance * m_right;
	m_model_view_needs_update = true;
}

// Move "distance" units along the up vector
void
Camera::moveUp    ( float distance )
{
	m_position += distance * m_up;
	m_model_view_needs_update = true;
}

// Move "distance" units along the back vector
void
Camera::moveBack  ( float distance )
{
	m_position += distance * m_back;
	m_model_view_needs_update = true;
}

void
Camera::yaw ( float degrees )
{
	rotate( 0, degrees, 0 );
}

// Rotate the camera counterclockwise around the up vector
void
Camera::rotate (float pitch_delta, float yaw_delta, float roll_delta)
{
	m_pitch += pitch_delta;
	m_yaw += yaw_delta;
	m_roll += roll_delta;

	calculateUnitVectors();
}

// Set the position of the camera
void
Camera::setPosition ( const glm::vec3& position )
{
	m_position = position;
	m_begin_position = position;
	m_model_view_needs_update = true;
}

/*
Sets the unit vectors so that the interface provides support
	to have the camera have the desired orientation
*/
void
Camera::setUnitVectors (float pitch, float yaw, float roll)
{
	m_pitch = pitch;
	m_yaw = yaw;
	m_roll = roll;

	calculateUnitVectors();	
}

// Return the view matrix, only recomputing it if necessary
// You can use this matrix as the model-view matrix
glm::mat4
Camera::getViewMatrix ()
{
	if ( m_model_view_needs_update )
	{
		m_modelView = glm::lookAt( m_position, m_position - m_back, m_up );
		m_model_view_needs_update = false;
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

	m_projection_needs_update = true;
}

// Return the projection matrix, only recomputing it if necessary
glm::mat4
Camera::getProjectionMatrix ()
{
	if ( m_projection_needs_update )
	{
		m_projection = glm::perspective( glm::radians( m_verticalFovDegrees ), 
			m_aspectRatio, m_nearZ, m_farZ );
		m_projection_needs_update = false;
	}
	return m_projection;
}

void
Camera::calculateUnitVectors()
{
	float sinX = glm::sin( glm::radians( m_pitch ));
	float cosX = glm::cos( glm::radians( m_pitch ));

	float sinY = glm::sin( glm::radians( m_yaw ));
	float cosY = glm::cos( glm::radians( m_yaw ));

	float sinZ = glm::sin( glm::radians( m_roll ));
	float cosZ = glm::cos( glm::radians( m_roll ));

    m_right.x = cosY * cosZ;
    m_right.y = sinX * sinY * cosZ + cosX * sinZ;
    m_right.z = sinX * sinZ - cosX * sinY * cosZ;

    m_up.x = -cosY * sinZ;
    m_up.y = cosX * cosZ - sinX * sinY * cosZ;
    m_up.z = cosX * sinY * sinZ + sinX * cosZ;

    m_back.x = sinY;
    m_back.y = -sinX * cosY;
    m_back.z = cosX * cosY;

    m_model_view_needs_update = true;
}
