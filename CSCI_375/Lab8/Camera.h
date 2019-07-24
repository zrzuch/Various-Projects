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

#include "Transform.h"
#include "Matrix4.h"

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

	const Matrix3&
	getEyeMatrix() const;

	// Return the view matrix, only recomputing it if necessary
	// You can use this matrix as the model-view matrix
	Transform
	getViewMatrix () const;

	const Transform&
	getViewMatrix (bool getConst) const;

	// Decrement the field of view (FOV) by "verticalFovDelta".
	// Clamp the FOV to the range [ 1, 120 ] degrees. 
	void
	zoom (double verticalFovDelta);

	void
	setAspectRatio(double aspectRatio);

	void
	setProjection();

	void
	setProjection(double verticalFovDegrees);

	// Set the camera to use a symmetric perspective projection.
	// NOTE we are now using double-s, which should be reflected
	//   in relevant data members.
	// For all projection methods, farZ > nearZ > 0. 
	void
	setProjection (double verticalFovDegrees, double aspectRatio,
	               double nearZ, double farZ);

	// Set the camera to use an asymmetric perspective projection.
	void
	setProjection (double left, double right, double bottom, double top,
               double nearZ, double farZ);

	// Set the camera to use an orthographic projection.
	void
	setOrthoProjection (double left, double right, double bottom, double top,
                    double nearZ, double farZ);

	// Return the projection matrix, only recomputing it if necessary
	Matrix4
	getProjectionMatrix () const;

	double
	getXFOV() const;

	double
	getYFOV() const;

private:

	enum class ProjectionType
	{
		SYMMETRIC,
		ASYMMETRIC,
		ORTHOGRAPHIC
	};

	mutable bool m_updateView;
	mutable bool m_updateProjection;
	ProjectionType m_currProjection;

	double m_left;
	double m_right;
	double m_bottom;
	double m_top;

	double m_fov;
	// Save the begin fov so that it can be reset when in Symmetric Projection
	double m_beginFov;
	// Should keep track in case window is resized
	double m_aspectRatio;
	// Used for every projection mostly likely will be the same for all
	double m_nearZ;
	double m_farZ;

	Transform m_world;
	Transform m_beginWorld;

	mutable Matrix4 m_projection;
	mutable Transform m_modelView;
};

#endif