#include "LightCollection.h"

Intensity::Intensity()
: diffuse(1)
, specular(1)
, m_updateDiffuse(true)
, m_updateSpecular(true)
{ }

void
Intensity::setDiffuse(Vector3 d)
{
	diffuse = d;
	m_updateDiffuse = true;
}

void
Intensity::setSpecular(Vector3 s)
{
	specular = s;
	m_updateSpecular = true;
}

Vector3
Intensity::getDiffuse()
{
	return diffuse;
}

Vector3
Intensity::getSpecular()
{
	return specular;
}

void
Intensity::setUniforms(ShaderProgram* shaderProgram, int index)
{
	const std::string lightIndex = "uLight[" + std::to_string(index) + "].";

	if (m_updateDiffuse)
	{
		shaderProgram->setUniform(lightIndex + "diffuse", diffuse);
		m_updateDiffuse = false;
	}

	if (m_updateSpecular)
	{
		shaderProgram->setUniform(lightIndex + "specular", specular);
		m_updateSpecular = false;
	}
}

Light::Light()
: intensity()
, position(10,10,10)
, direction(0,0,1)

, m_attenuation(0.01f, 0.02f, 0.05f)
, m_angleOfLight(0)
, m_falloff(2)
, m_isDirect(false)
, m_isActive(false)

, m_updateAttenuation(true)
, m_updateAngleOfLight(true)
, m_updateFalloff(true)
, m_updateIsDirect(true)
, m_updateIsActive(true)
{ }

void
Light::setAngleOfLight(float angle)
{
	m_angleOfLight = angle;
	m_updateAngleOfLight = true;
}

void
Light::setFalloff(float dist)
{
	m_falloff = dist;
	m_updateFalloff = true;
}

void
Light::setAttenuation(const Vector3& attenuation)
{
	m_attenuation = attenuation;
	m_updateAttenuation = true;
}

void
Light::setIsDirect(bool d)
{
	m_isDirect = d;
	m_updateIsDirect = true;
}

void
Light::setIsActive(bool a)
{
	m_isActive = a;
	m_updateIsActive = true;
}

Vector3
Light::getAttenuation()
{
	return m_attenuation;
}

float
Light::getAngleOfLight()
{
	return m_angleOfLight;
}

float
Light::getFalloff()
{
	return m_falloff;
}

bool
Light::isDirectionalLight()
{
	return m_isDirect;
}

bool
Light::isActiveLight()
{
	return m_isActive;
}

void
Light::setUniforms(ShaderProgram* shaderProgram, int index)
{
	const std::string lightIndex = "uLight[" + std::to_string(index) + "].";

	if (m_updateAttenuation)
	{
		shaderProgram->setUniform(lightIndex + "attenuation", m_attenuation);
		m_updateAttenuation = false;
	}

	if (m_updateAngleOfLight)
	{
		shaderProgram->setUniform(lightIndex + "angleOfVisibility", m_angleOfLight);
		m_updateAngleOfLight = false;
	}

	if (m_updateFalloff)
	{
		shaderProgram->setUniform(lightIndex + "falloff", m_falloff);
		m_updateFalloff = false;
	}

	if (m_updateIsDirect)
	{
		shaderProgram->setUniform(lightIndex + "isDirect", m_isDirect);
		m_updateIsDirect = false;
	}

	if (m_updateIsActive)
	{
		shaderProgram->setUniform(lightIndex + "isActive", m_isActive);
		m_updateIsDirect = false;
	}
}

LightCollection::LightCollection(unsigned numLights)
: m_lights(numLights)
{ }

Light&
LightCollection::operator[](int index)
{
	return m_lights[index];
}

unsigned
LightCollection::size()
{
	return m_lights.size();
}

void
LightCollection::setUniforms(ShaderProgram* shaderProgram, Camera& camera)
{
	for (unsigned i = 0; i < m_lights.size(); ++i)
	{
		m_lights[i].setUniforms(shaderProgram, i);
		if (m_lights[i].isActiveLight())
		{
			m_lights[i].intensity.setUniforms(shaderProgram, i);

			std::string lightStruct = "uLight[" + std::to_string(i) + "].";
			if (!m_lights[i].isDirectionalLight())
			{
				shaderProgram->setUniform(lightStruct + "position", 
					camera.getViewMatrix().translate(m_lights[i].position));
				if (m_lights[i].getAngleOfLight() > 0.0f)
				{
					shaderProgram->setUniform(lightStruct + "direction", 
						camera.getViewMatrix().getOrientation() * m_lights[i].direction);
				}
			}
			else
			{
				shaderProgram->setUniform(lightStruct + "direction", 
					camera.getViewMatrix().getOrientation() * m_lights[i].direction);
			}
		}
	}
}