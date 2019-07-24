#include <utility>
#include <iostream>

#include "Model.h"
#include "AiScene.h"

/*
LEAK SUMMARY:
==1801==    definitely lost: 775 bytes in 2 blocks
==1801==    indirectly lost: 0 bytes in 0 blocks
==1801==      possibly lost: 7,341,888 bytes in 8 blocks
==1801==    still reachable: 669,807 bytes in 1,945 blocks
==1801==         suppressed: 0 bytes in 0 blocks
*/

Model::Model(const std::string& filename, const Transform& beginOrientation)
  : m_meshes()
  , m_textures()
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
	for (unsigned i = 0; i < m_meshes.size(); ++i)
	{
		delete m_meshes[i];
	}
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
	std::vector<std::vector<float>> vertexData = scene.getAllVertexDataSeperate();
	std::vector<std::vector<unsigned>> indices = scene.getAllFaceIndicesSeperate();
	std::vector<std::string> files = scene.getAllTexturePaths();
	std::vector<std::pair<std::vector<unsigned>, std::vector<float>>> boneData = scene.getAllBoneData();
	m_bone = scene.getBones();
	// printBoneMatrices(m_bone, m_bone, 0, 1);
	for (unsigned meshNum = 0; meshNum < files.size(); ++meshNum)
	{
		Mesh* mesh;
		if (boneData.size() == 0)
		{
			mesh = new Mesh(vertexData[meshNum], indices[meshNum]);
		}
		else
		{
			mesh = new Mesh(vertexData[meshNum], indices[meshNum], boneData[meshNum].second,
				boneData[meshNum].first);
		}
		
		std::string file = getProperPath(files[meshNum]);

		if (file != "")
		{
			auto itr = m_textures.find(file);
			if (itr == m_textures.end())
			{
				m_textures.insert({ file, new Texture(file) });
			}
		}
		mesh->textureFilePath = file;
		m_meshes.push_back(mesh);
	}
	if (m_bone != nullptr)
	{
		m_transforms.push_back(Transform());
	}
	else
	{
		m_transforms.push_back(beginOrientation);
	}
}

std::string
Model::getProperPath(const std::string& file)
{
	std::string fileName = file;
	size_t slash = fileName.find("//");
	while (slash != std::string::npos)
	{
		if (slash == 0)
		{
			fileName.erase(slash, 2);
		}
		else
		{
			fileName.replace(slash, 2, "/");
		}
		slash = fileName.find("//");
	}

	slash = fileName.find("\\");
	while (slash != std::string::npos)
	{
		if (slash == 0)
		{
			fileName.erase(slash, 1);
		}
		else
		{
			fileName.replace(slash, 1, "/");
		}
		slash = fileName.find("\\");
	}

	slash = fileName.find("/");
	if (slash == 0)
	{
		fileName.erase(slash, 1);
	}

	return fileName;
}

void
Model::prepare()
{
	for (Mesh* mesh : m_meshes)
	{
		mesh->prepareVao();
	}
	for (std::pair<std::string, Texture*> texPair : m_textures)
	{
		texPair.second->prepare();
	}
}

void
Model::draw(ShaderProgram* shaderProgram, const Camera& camera)
{
	shaderProgram->enable ();
	draw(shaderProgram, camera, true);
	shaderProgram->disable ();
}

void
Model::draw(ShaderProgram* shaderProgram, const Camera& camera, bool isShaderHandled)
{
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
		shaderProgram->setUniform ("uModelView", worldView.getTransform());

		Matrix3 normalMatrix = worldView.getOrientation();
		normalMatrix.invert();
		normalMatrix.transpose();
		shaderProgram->setUniform ("uNormalMatrix", normalMatrix);

		for (Mesh* mesh : m_meshes)
		{
			shaderProgram->setUniform ("uHasTexture", mesh->hasTexture());
			if (mesh->hasTexture())
			{
				m_textures[mesh->textureFilePath]->bind();
				mesh->draw();
				m_textures[mesh->textureFilePath]->unbind();
			}
			else 
			{
				mesh->draw();
			}
		}
	}
}

void
Model::addCopy(Transform transform)
{
  m_transforms.push_back(transform);
}

unsigned
Model::numVertices()
{
	unsigned size = 0;
	for (Mesh* mesh : m_meshes)
	{
		size += mesh->numVertices();
	}
	return size;
}

unsigned
Model::numIndices()
{
	unsigned size = 0;
	for (Mesh* mesh : m_meshes)
	{
		size += mesh->numIndices();
	}
	return size;
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