#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "Mesh.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Frustum.h"
#include "Texture.h"
#include "Transform.h"
#include "Debug.h"

class MeshNode
{
public:
	MeshNode(const std::vector<std::vector<float>>& 									vertexData,
			 const std::vector<std::vector<unsigned>>& 									indices,
			 const std::vector<std::string>& 											texturePaths,
		 	 const std::vector<std::pair<std::vector<unsigned>, std::vector<float>>>& 	boneData);

	~MeshNode();

	void
	getCovarianceHierarchy(Vector3& center, Matrix3& covariance);

	void
	getCenterOfHierarchy(unsigned& n, Vector3& massCenter);

	void
	getOrientedHierarchy(std::vector<float>& lrbtnf, Matrix3& rotation);

	void
	calculateSphereHierarchy();

	std::vector<float>
	calculateBoxHierarchy();

	void
	calculateLocalOrientedBoxHierarchy();

	void
	compareBoxLimits(std::vector<float>& box, const std::vector<float>& childBox);

	void
	getFarthestLength(SphereBV& sphere);

	unsigned
	draw(ShaderProgram* shaderProgram, Transform& modelView, Matrix3& normal, SphereDebug& sphereD, Frustum& planes, std::unordered_map<std::string, Texture*>& textures);

	std::vector<MeshNode*> children;
	std::vector<Mesh*> meshes;
	Vector3 sum;
	float numVerts;
	unsigned numInds;
	SphereBV sphere;
	SphereBV localSphere;
	BoxBV box;
	BoxBV localBox;
	BoxBV orientedBox;
	BoxBV localOrientedBox;
	// Transform local;
	static constexpr unsigned NUM_INDICES_PER_TRIANGLE = 3;

private:

	Matrix3 
	calculateAxisMatrix(Matrix3& covarianceMatrix);
};