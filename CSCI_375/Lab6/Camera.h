/*
  FileName    : Camera.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 4
  Description : This file is the camera header file which has the interface
  				for the camera.
*/

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/mat4x4.hpp>

#include "Transform.h"

class Camera
{

public:

	Camera ();

	void
	reset();

	void
	moveRight (float distance);

	void
	moveUp    (float distance);

	void
	moveBack  (float distance);

	void
	pitch (float degrees);

	void
	yaw (float degrees);

	void
	roll (float degrees);

	void
	setPosition (float x, float y, float z);

	void
	setPosition (const Vector3& position);

	void
	setUnitVectors (const Transform& world);

	// Align local Y with world Y. Adjust other basis vectors
	//   so they are orthonormal. 
	void
	alignWithWorldY ();

	// Return the view matrix, only recomputing it if necessary
	// You can use this matrix as the model-view matrix
	Transform
	getViewMatrix () const;

	// Set the projection parameters
	void
	setProjection (float verticalFovDegrees, float aspectRatio,
	               float nearZ, float farZ); 

	// Return the projection matrix, only recomputing it if necessary
	glm::mat4
	getProjectionMatrix () const;

private:
	
	mutable bool m_updateModelView;

	Transform m_world;
	Transform m_beginWorld;

	glm::mat4 m_projection;
	mutable Transform m_modelView;
};

#endif