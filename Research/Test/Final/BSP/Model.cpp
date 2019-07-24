#include <utility>
#include <iostream>

#include "Model.h"
#include "AiScene.h"
#include "Frustum.h"

/*
LEAK SUMMARY:
==1801==    definitely lost: 775 bytes in 2 blocks
==1801==    indirectly lost: 0 bytes in 0 blocks
==1801==      possibly lost: 7,341,888 bytes in 8 blocks
==1801==    still reachable: 669,807 bytes in 1,945 blocks
==1801==         suppressed: 0 bytes in 0 blocks
*/

Model::Model(const std::string& filename, const Transform& beginOrientation)
  : m_textures()
  , m_transforms()
  , name(filename)
{
	if (filename != "")
	{
		importFromFile(filename, beginOrientation);
	}
}

Model::~Model()
{
	delete root;
  	for (std::pair<std::string, Texture*> pTexture : m_textures)
  	{
  		delete pTexture.second;
  	}
  	delete m_bone;
}

int
printBoneMatrices(Bone* bone, Bone* parent, int depth, int i)
{
	std::cout << "Parent Bone = " << parent->name << std::endl;
	std::cout << "This Bone   = " << bone->name << std::endl;
	std::cout << "Depth       = " << depth << std::endl;
	std::cout << "Node Num    = " << i << std::endl;
	std::cout << bone->bind;

	for (Bone* child : bone->children)
	{
		i = printBoneMatrices(child, bone, depth + 1, i + 1);
	}
	return i;
}

void
Model::importFromFile(const std::string& filename, const Transform& beginOrientation)
{
	AiScene scene(filename, beginOrientation);
	std::vector<std::string> files = scene.getAllTexturePaths();
	for (unsigned i = 0; i < files.size(); ++i)
	{
		if (files[i] != "")
		{
			auto itr = m_textures.find(files[i]);
			if (itr == m_textures.end())
			{
				m_textures.insert({ files[i], new Texture(files[i]) });
			}
		}
	}
	

	root = scene.getMeshHierarchy();
	root->calculateSphereHierarchy();
	root->calculateBoxHierarchy();

	m_bone = scene.getBones();
	if (m_bone != nullptr)
	{
		m_transforms.push_back(Transform());
	}
	else
	{
		m_transforms.push_back(beginOrientation);
	}
}

unsigned
Model::draw(ShaderProgram* shaderProgram, const Camera& camera, SphereDebug& sphere)
{
	shaderProgram->enable ();
	unsigned numTriangles = draw(shaderProgram, camera, sphere, true);
	shaderProgram->disable();
	return numTriangles;
}

unsigned
Model::draw(ShaderProgram* shaderProgram, const Camera& camera, SphereDebug& sphere, bool isShaderHandled)
{
	unsigned numTriangles = 0;
	if (m_bone != nullptr)
	{
		m_bone->setUniforms(shaderProgram);
		shaderProgram->setUniform ("hasBones", true);
	}
	else
	{
		shaderProgram->setUniform ("hasBones", false);
	}
	material.setUniforms(shaderProgram);
	for (const Transform& world : m_transforms)
	{
		Transform worldView = camera.getViewMatrix();
		worldView.combine(world);

		Matrix4 MVP = camera.getProjectionMatrix();
		MVP *= worldView.getTransform();
		// Transpose to match proper elements since algorithm uses the transpose of my matrix
		MVP.transpose();

		Frustum planes( MVP );

		material.setUniforms(shaderProgram);

		// if (planes.inFrustum(sphere))
		if (planes.inFrustum(root->sphere))
		{
			Matrix3 normalMatrix = worldView.getOrientation();
			normalMatrix.invert();
			normalMatrix.transpose();
			
			numTriangles += root->draw(shaderProgram, worldView, normalMatrix, sphere, planes, m_textures);
		}
	}
	return numTriangles;
}

void
Model::addCopy(Transform transform)
{
  m_transforms.push_back(transform);
}

unsigned
Model::numTransforms()
{
	return m_transforms.size();
}

Transform&
Model::getTransform(int index)
{
  return m_transforms[index];
}

float
Model::getRadius()
{
	return root->sphere.radius;
}

Vector3
Model::getCenter()
{
	return root->sphere.center;
}