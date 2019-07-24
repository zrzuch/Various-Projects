#include "Scene.h"
#include "Math.h"
#include <iostream>

Scene::Scene()
	: camera()
	, mouseBuffer()
	, models(new ModelController())
	, lights()
    , sphere()
{ }

Scene::~Scene()
{
    delete models;
}

unsigned
Scene::draw(ShaderProgram* shaderProgram)
{
	shaderProgram->enable ();

	shaderProgram->setUniform ("uProjection", camera.getProjectionMatrix());

	lights.setUniforms(shaderProgram, camera);

	unsigned numTriangles = models->draw(shaderProgram, camera, sphere, true);

	shaderProgram->disable ();

    return numTriangles;
}

void
Scene::setAspectRatio(double width, double height)
{
	camera.setAspectRatio(width / height);
    mouseBuffer.setWidth(width);
    mouseBuffer.setHeight(height);
    updateMouseBuffer();
}

void
Scene::setZoom(double deltaFov)
{
	camera.zoom(deltaFov);
    updateMouseBuffer();
}

void
Scene::processDrag(double x, double y)
{
	if (mouseBuffer.isLeftClicked())
    {
        mouseBuffer.translate(x, y);
        if (x > 0)
        {
        	camera.yaw(mouseBuffer.getXDegrees());
        	camera.pitch(mouseBuffer.getYDegrees());
        }
        else
        {
        	camera.pitch(mouseBuffer.getYDegrees());
        	camera.yaw(mouseBuffer.getXDegrees());
        }
    }
    else if (mouseBuffer.isRightClicked())
    {
        mouseBuffer.translate(x, y);
        camera.roll(mouseBuffer.getXDegrees());
    }
}

void
Scene::setToSymmetric ()
{
	camera.setProjection();
	updateMouseBuffer();
}

void
Scene::setToAsymmetric (double left, double right, double bottom, double top,
           double nearZ, double farZ)
{
	camera.setProjection(-0.075f, 0.125f, -0.075f, 0.125f, 0.1f, 120.0f);
	updateMouseBuffer();
}

void
Scene::setToOrtho (double left, double right, double bottom, double top,
                double nearZ, double farZ)
{
	camera.setOrthoProjection(-15.0f, 15.0f, -15.0f, 15.0f, 0.1f, 120.0f);
	updateMouseBuffer();
}

void
Scene::updateMouseBuffer()
{
	mouseBuffer.setXFOV(camera.getXFOV());
    mouseBuffer.setYFOV(camera.getYFOV());
}