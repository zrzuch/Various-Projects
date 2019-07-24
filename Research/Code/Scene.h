#ifndef SCENE_H
#define SCENE_H

#include "ModelController.h"
#include "LightCollection.h"
#include "MouseBuffer.h"

class Scene
{
public:
	// All public since the implementation will not change
	//	when these are interacted with. These objects are just
	// 	aggregated together since they are associated.
	Camera camera;
	MouseBuffer mouseBuffer;
	ModelController* models;
	LightCollection lights;

	Scene();

	~Scene();

	// Disable default copy ctor and copy assignment
  	Scene (const Scene&) = delete;
  	Scene& operator= (const Scene&) = delete;

  	void
	prepare();

  	void
	draw(ShaderProgram* shaderProgram);

	void
	setAspectRatio(double width, double height);

	void
	setZoom(double deltaFov);

	void
	processDrag(double x, double y);

	void
	setToSymmetric ();

	// Set the camera to use an asymmetric perspective projection.
	void
	setToAsymmetric (double left, double right, double bottom, double top,
               double nearZ, double farZ);

	// Set the camera to use an orthographic projection.
	void
	setToOrtho (double left, double right, double bottom, double top,
                    double nearZ, double farZ);

	void
	updateMouseBuffer();
};

#endif