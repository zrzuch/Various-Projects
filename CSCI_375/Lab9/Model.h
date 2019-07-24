#pragma once

#include <string>
#include <unordered_map>

#include "Transform.h"
#include "Texture.h"
#include "Camera.h"
#include "Mesh.h"
#include "Animation.h"
#include "Material.h"

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

    void
    prepare();

    void 
    draw(ShaderProgram* shaderProgram, const Camera& camera);

	void
	draw(ShaderProgram* shaderProgram, const Camera& camera, bool isShaderHandled);

	void
	addCopy(Transform transform = Transform());

	unsigned
	numVertices();

	unsigned
	numIndices();

	unsigned
	numTransforms();

	Transform&
	getTransform(int index);

private:
	std::vector<Mesh*> m_meshes;
	std::unordered_map<std::string, Texture*> m_textures;
	std::vector<Transform> m_transforms;
public:
	Bone* m_bone;
	std::string name;
	Material material;
};
