#include "MeshNode.h"

MeshNode::MeshNode( const std::vector<std::vector<float>>& 										vertexData,
		 			const std::vector<std::vector<unsigned>>& 									indices,
		 			const std::vector<std::string>& 											texturePaths,
	 	 			const std::vector<std::pair<std::vector<unsigned>, std::vector<float>>>& 	boneData)
: sum(0)
, numVerts(0)
, numInds(0)
{
	if (boneData.size() == 0)
	{
		for (unsigned i = 0; i < vertexData.size(); ++i)
		{
			meshes.push_back(new Mesh(vertexData[i], indices[i], texturePaths[i]));
		}
	}
	else
	{
		for (unsigned i = 0; i < vertexData.size(); ++i)
		{
			meshes.push_back(new Mesh(vertexData[i], indices[i], texturePaths[i], boneData[i].second, boneData[i].first));
		}
	}
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		meshes[i]->prepareVao();
	}
}

MeshNode::~MeshNode()
{
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		delete meshes[i];
	}
	for (unsigned i = 0; i < children.size(); ++i)
	{
		delete children[i];
	}
}

void
MeshNode::calculateSphereHierarchy()
{
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		sum += meshes[i]->getMassSum();
		numVerts += meshes[i]->numVertices();
		numInds += meshes[i]->numIndices();
		std::cout << "Number of Indices = " << meshes[i]->numIndices() << std::endl;
	}
	
	localSphere.center = sum / numVerts;

	for (unsigned i = 0; i < children.size(); ++i)
	{
		children[i]->calculateSphereHierarchy();
		numVerts += children[i]->numVerts;
		sum += children[i]->sum;
	}
	sphere.center = sum / numVerts;

	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		meshes[i]->getRadius(localSphere);
	}
	sphere.radius = localSphere.radius;

	for (unsigned i = 0; i < children.size(); ++i)
	{
		children[i]->getFarthestLength(sphere);
	}
}

std::vector<float>
MeshNode::calculateBoxHierarchy()
{
	std::vector<float> lrbtnf(6);
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		meshes[i]->getBoxBV(lrbtnf);
	}
	localBox.init(lrbtnf);

	for (unsigned i = 0; i < children.size(); ++i)
	{
		std::vector<float> childBox = children[i]->calculateBoxHierarchy();
		compareBoxLimits(lrbtnf, childBox);
	}
	box.init(lrbtnf);
	return lrbtnf;
}

void
MeshNode::compareBoxLimits(std::vector<float>& box, const std::vector<float>& childBox)
{
	// left
	if (childBox[0] < box[0]) box[0] = childBox[0];
	// right
	if (childBox[1] > box[1]) box[1] = childBox[1];
	// bottom
	if (childBox[2] < box[2]) box[2] = childBox[2];
	// top
	if (childBox[3] > box[3]) box[3] = childBox[3];
	// near
	if (childBox[4] < box[4]) box[4] = childBox[4];
	// far
	if (childBox[5] > box[5]) box[5] = childBox[5];
}

void
MeshNode::getFarthestLength(SphereBV& sphere)
{
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		meshes[i]->getRadius(sphere);
	}
	for (unsigned i = 0; i < children.size(); ++i)
	{
		children[i]->getFarthestLength(sphere);
	}
}

unsigned
MeshNode::draw(ShaderProgram* shaderProgram, Transform& modelView, Matrix3& normal, SphereDebug& sphereD, Frustum& planes, std::unordered_map<std::string, Texture*>& textures)
{
	unsigned numTriangles = 0;
	if (planes.inFrustum(sphere))
	{
		// if (children.size() == 0 || planes.inFrustum(localBox))
		// {
			shaderProgram->setUniform ("uModelView", modelView.getTransform());
			shaderProgram->setUniform ("uNormalMatrix", normal);
			for (unsigned i = 0; i < meshes.size(); ++i)
			{
				if (meshes[i]->hasTexture())
				{
					shaderProgram->setUniform ("uHasTexture", meshes[i]->hasTexture());
					std::cout << meshes[i]->textureFilePath << std::endl;
					textures[meshes[i]->textureFilePath]->bind();
					meshes[i]->draw();
					textures[meshes[i]->textureFilePath]->unbind();
				}
				else
				{
					meshes[i]->draw();
				}
			}
			sphereD.init(localBox);
			sphereD.draw(shaderProgram, modelView);

			numTriangles += numInds / NUM_INDICES_PER_TRIANGLE;
		// }
		for (unsigned i = 0; i < children.size(); ++i)
		{
			numTriangles += children[i]->draw(shaderProgram, modelView, normal, sphereD, planes, textures);
		}
	}
	return numTriangles;
}
