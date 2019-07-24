#pragma once

#include "Frustum.h"
#include "Transform.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Material.h"

class SphereDebug
{
public:

	enum class BVType
	{
		SPHERE, BOX
	};

	SphereDebug();

	~SphereDebug();

	void
	init(const SphereBV& sphereBV);

	void
	init(const BoxBV& boxBV);

	void
	draw(ShaderProgram* shaderProgram, Transform modelView);

private:
	Mesh* sphereMesh;
	Mesh* boxMesh;
	BVType type;
public:

	Transform local;
	Material material;
};