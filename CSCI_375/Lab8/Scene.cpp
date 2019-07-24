#include "Scene.h"
#include "Math.h"
#include <iostream>

Scene::Scene()
	: camera()
	, mouseBuffer()
	, meshes()
	, m_lightSource(0,0,4)
	, m_lightDir(0,0,1)
	, m_lightIntensity(0.5, 0.2, 0.1)
{ }

void
Scene::prepare()
{
	for (unsigned i = 0; i < meshes.numMesh(); ++i)
	{
		meshes.getMesh(i)->prepareVao();
	}
}

void
Scene::draw(ShaderProgram* shaderProgram)
{
	shaderProgram->enable ();

	shaderProgram->setUniformMatrix ("uLightSource", m_lightSource);
	shaderProgram->setUniformMatrix ("uLightDir", m_lightDir);
	shaderProgram->setUniformMatrix ("uLightIntensity", m_lightIntensity);

	for (unsigned i = 0; i < meshes.numMesh(); ++i)
	{
		if (meshes.isDrawing(i))
		{
			meshes.getMesh(i)->draw(shaderProgram, camera, true);
		}
	}
	shaderProgram->disable ();
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