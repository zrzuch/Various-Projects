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

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

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
	setPosition ( const glm::vec3& position );

	// returns bool for whether or not the unit vectors were changed
	void
	setUnitVectors (float pitch, float yaw, float roll);

	// Return the view matrix, only recomputing it if necessary
	// You can use this matrix as the model-view matrix
	glm::mat4
	getViewMatrix ();

	// Set the projection parameters
	void
	setProjection (float verticalFovDegrees, float aspectRatio,
	               float nearZ, float farZ); 

	// Return the projection matrix, only recomputing it if necessary
	glm::mat4
	getProjectionMatrix ();

private:

	void
	calculateUnitVectors ();
	
	bool m_model_view_needs_update;
	bool m_projection_needs_update;

	float m_pitch;
	float m_begin_pitch;

	float m_yaw;
	float m_begin_yaw;

	float m_roll;
	float m_begin_roll;

	glm::vec3 m_position;
	glm::vec3 m_begin_position;

	glm::vec3 m_right;
	glm::vec3 m_up;
	glm::vec3 m_back;

	glm::mat4 m_projection;
	glm::mat4 m_modelView;

	float m_verticalFovDegrees; 
	float m_aspectRatio;
	float m_nearZ; 
	float m_farZ;
};

#endif