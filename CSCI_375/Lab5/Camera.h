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

#include "Vector3.h"
#include "Matrix3.h"

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
	pitch (float degrees);

	void
	yaw (float degrees);

	void
	roll (float degrees);

	void
	setPosition ( const Vector3& position );

	void
	setUnitVectors (Matrix3& local);

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
	
	mutable bool m_updateModelView;

	Vector3 m_position;
	Vector3 m_beginPosition;

	Matrix3 m_local;
	Matrix3 m_beginLocal;

	glm::mat4 m_projection;
	mutable glm::mat4 m_modelView;

	float m_verticalFovDegrees; 
	float m_aspectRatio;
	float m_nearZ; 
	float m_farZ;
};

#endif