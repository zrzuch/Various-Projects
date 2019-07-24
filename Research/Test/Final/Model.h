#pragma once

#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"
#include "Animation.h"
#include "Material.h"
#include "MeshNode.h"
#include "Debug.h"
#include "BSPTree.h"

class Model
{
public:

	Model(const std::string& filename = "", const Transform& beginOrientation = Transform());

	~Model();

	// Disable default copy ctor and copy assignment
    Model (const Model&) = delete;
    Model& operator= (const Model&) = delete;

    void
    importFromFile(const std::string& filename, const Transform& beginOrientation = Transform());

    std::string
    getProperPath(const std::string& file);

    unsigned 
    draw(ShaderProgram* shaderProgram, const Camera& camera, SphereDebug& sphere);

	unsigned
	draw(ShaderProgram* shaderProgram, const Camera& camera, SphereDebug& sphere, bool isShaderHandled);

	void
	addCopy(Transform transform = Transform());

	unsigned
	numTransforms();

	Transform&
	getTransform(int index);

	float
	getRadius();

	Vector3
	getCenter();

private:
	MeshNode* root;
	std::unordered_map<std::string, Texture*> m_textures;
	std::vector<Transform> m_transforms;
	BSPTree* bspRoot;
public:
	Bone* m_bone;
	std::string name;
	Material material;
};
