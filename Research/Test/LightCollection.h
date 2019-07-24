#pragma once

#include "ShaderProgram.h"
#include "Camera.h"
#include <vector>

class Intensity
{
public:

	Intensity();

	~Intensity() = default;

	void
	setDiffuse(Vector3 d);

	void
	setSpecular(Vector3 s);

	Vector3
	getDiffuse();

	Vector3
	getSpecular();

	void
	setUniforms(ShaderProgram* shaderProgram, int index);

private:

	Vector3 diffuse;
	Vector3 specular;

	bool m_updateDiffuse;
	bool m_updateSpecular;

};

class Light
{
public:

	Intensity intensity;
	// Different Depending on the type of light either a Direction or a Light 
	// 	Source in world space so it has to be set everytime by translating it 
	// 	by the view matrix
	Vector3 position;
	Vector3 direction;

	Light();

	~Light() = default;

	void
	setAngleOfLight(float angle);

	void
	setFalloff(float dist);

	void
	setAttenuation(const Vector3& attenuation);

	void
	setIsDirect(bool d);

	void
	setIsActive(bool d);

	Vector3
	getAttenuation();

	float
	getAngleOfLight();

	float
	getFalloff();

	bool
	isDirectionalLight();

	bool
	isActiveLight();

	void
	setUniforms(ShaderProgram* shaderProgram, int index);

private:
	
	Vector3 m_attenuation;
	// Angle for Spot Lights
	float m_angleOfLight;
	float m_falloff;
	bool m_isDirect;
	bool m_isActive;

	bool m_updateAttenuation;
	bool m_updateAngleOfLight;
	bool m_updateFalloff;
	bool m_updateIsDirect;
	bool m_updateIsActive;
};

class LightCollection
{
public:

	LightCollection(unsigned numLights = 8);

	Light&
	operator[](int index);

	unsigned
	size();

	void
	setUniforms(ShaderProgram* shaderProgram, Camera& camera);

private:

	std::vector<Light> m_lights;
};