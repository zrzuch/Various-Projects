/*
  FileName    : Camera.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 3
  Description : This file is the camera header file which has the interface
  				for the camera.
*/

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/mat4x4.hpp>

#include "Vector3.h"

class Camera
{

public:

	Camera ();

	~Camera ();

	void
	reset();

	void
	moveRight (float distance);

	void
	moveUp    (float distance);

	void
	moveBack  (float distance);

	void
	yaw (float degrees);
	
	void
	rotate (float pitch, float yaw, float roll);

	void
	setPosition ( const Vector3& position );

	void
	setUnitVectors (float pitch, float yaw, float roll);

	// Return the view matrix, only recomputing it if necessary
	// You can use this matrix as the model-view matrix
	glm::mat4
	getViewMatrix () const;

	// Set the projection parameters
	void
	setProjection (float verticalFovDegrees, float aspectRatio,
	               float nearZ, float farZ); 

	// Return the projection matrix, only recomputing it if necessary
	glm::mat4
	getProjectionMatrix () const;

private:

	void
	calculateUnitVectors ();

	void
	calculateProjection ();
	
	mutable bool m_model_view_needs_update;

	float m_pitch;
	float m_begin_pitch;

	float m_yaw;
	float m_begin_yaw;

	float m_roll;
	float m_begin_roll;

	Vector3 m_position;
	Vector3 m_begin_position;

	Vector3 m_right;
	Vector3 m_up;
	Vector3 m_back;

	glm::mat4 m_projection;
	mutable glm::mat4 m_modelView;

	float m_verticalFovDegrees; 
	float m_aspectRatio;
	float m_nearZ; 
	float m_farZ;
};

#endif