#include "MeshNode.h"
#include <gsl/gsl_eigen.h>

MeshNode::MeshNode( const std::vector<std::vector<float>>& 									vertexData,
		 			const std::vector<std::vector<unsigned>>& 							indices,
		 			const std::vector<std::string>& 									texturePaths,
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

/*void
MeshNode::calculateCenter()
{
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		sum += meshes[i]->getMassSum();
		numVerts += meshes[i]->numVertices();
		numInds += meshes[i]->numIndices();
	}
	localSphere.center = sum / numVerts;

	for (unsigned i = 0; i < children.size(); ++i)
	{
		children[i]->calculateCenter();
		numVerts += children[i]->numVerts;
		sum += children[i]->sum;
	}
	sphere.center = sum / numVerts;
}*/

// Pre-Condition Calculate Center 
void
MeshNode::calculateSphereHierarchy()
{
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		sum += meshes[i]->getMassSum();
		numVerts += meshes[i]->numVertices();
		numInds += meshes[i]->numIndices();
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
	std::vector<float> lrbtnf;
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		meshes[i]->getBoxBV(lrbtnf);
	}
	localBox.init(lrbtnf);

	for (unsigned i = 0; i < children.size(); ++i)
	{
		compareBoxLimits(lrbtnf, children[i]->calculateBoxHierarchy());
	}
	box.init(lrbtnf);
	return lrbtnf;
}

Matrix3 
MeshNode::calculateAxisMatrix(Matrix3& covarianceMatrix)
{
	// setup for gsl library
	// gsl is a c function library so pointers 
	//	must be allocated and destroyed will explicit calls
	constexpr unsigned MATRIX_ROW_MAX = 3;
	gsl_eigen_symmv_workspace* w = gsl_eigen_symmv_alloc(MATRIX_ROW_MAX);
	gsl_matrix* cov = gsl_matrix_calloc(MATRIX_ROW_MAX, MATRIX_ROW_MAX);
	for (unsigned i = 0; i < MATRIX_ROW_MAX; ++i)
	{
		for (unsigned j = 0; j < MATRIX_ROW_MAX; ++j)
		{
			gsl_matrix_set(cov, i, j, covarianceMatrix.getValue(i,j));
		}
	}
	gsl_vector* eval = gsl_vector_calloc(MATRIX_ROW_MAX);
	gsl_matrix* evec = gsl_matrix_calloc(MATRIX_ROW_MAX, MATRIX_ROW_MAX);

	// gsl eigen call for real symmetric matrix which a covariance of primitve positions is
	gsl_eigen_symmv(cov, eval, evec, w);
	gsl_matrix_free(cov);
	gsl_eigen_symmv_free(w);
	gsl_vector_free(eval);

	// The three eigenvectors are the axises for the oriented bounding box
	std::vector<Vector3> eigenVectors;
	eigenVectors.reserve(3);

	eigenVectors.push_back(
	Vector3(
		gsl_matrix_get(evec, 0, 0),
		gsl_matrix_get(evec, 1, 0),
		gsl_matrix_get(evec, 2, 0)
	));

	eigenVectors.push_back(
	Vector3(
		gsl_matrix_get(evec, 0, 1),
		gsl_matrix_get(evec, 1, 1),
		gsl_matrix_get(evec, 2, 1)
	));

	eigenVectors.push_back(
	Vector3(
		gsl_matrix_get(evec, 0, 2),
		gsl_matrix_get(evec, 1, 2),
		gsl_matrix_get(evec, 2, 2)
	));
	gsl_matrix_free(evec);

	for (Vector3& eigenVector : eigenVectors)
	{
		eigenVector.normalize();
	}
	Matrix3 axis(eigenVectors[0], eigenVectors[1], eigenVectors[2]);
	return axis;
}

void
MeshNode::getCovarianceHierarchy(Vector3& center, Matrix3& covariance)
{
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		meshes[i]->getCovarianceMatrix(center, covariance);
	}
	for (unsigned i = 0; i < children.size(); ++i)
	{
		children[i]->getCovarianceHierarchy(center, covariance);
	}
}

void
MeshNode::getCenterOfHierarchy(unsigned& n, Vector3& massCenter)
{
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		massCenter += meshes[i]->getMassSum();
		n += meshes[i]->numVertices();
	}
	for (unsigned i = 0; i < children.size(); ++i)
	{
		children[i]->getCenterOfHierarchy(n, massCenter);
	}
}

void
MeshNode::getOrientedHierarchy(std::vector<float>& lrbtnf, Matrix3& rotation)
{
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		meshes[i]->getBoxBV(lrbtnf, rotation);
	}
	for (unsigned i = 0; i < children.size(); ++i)
	{
		children[i]->getOrientedHierarchy(lrbtnf, rotation);
	}
}

void
MeshNode::calculateLocalOrientedBoxHierarchy()
{
	Vector3 vectorSum(0);
	unsigned numV = 0;
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		vectorSum += meshes[i]->getMassSum();
		numV += meshes[i]->numVertices();
	}
	Vector3 localCenter = sum / numV;

	Matrix3 covarianceMatrix;
	covarianceMatrix.setToZero();
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		meshes[i]->getCovarianceMatrix(localCenter, covarianceMatrix);
	}

	/******************************************************************************/

	Matrix3 rotationMatrix = calculateAxisMatrix(covarianceMatrix);
	
	/******************************************************************************/

	rotationMatrix.invertRotation();
	std::vector<float> lrbtnf;
	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		meshes[i]->getBoxBV(lrbtnf, rotationMatrix);
	}
	rotationMatrix.invertRotation();
	localOrientedBox.init(lrbtnf, rotationMatrix);

	/******************************************************************************/

	for (unsigned i = 0; i < children.size(); ++i)
	{
		children[i]->getCenterOfHierarchy(numV, vectorSum);
	}
	Vector3 center = sum / numV;

	covarianceMatrix.setToZero();
	for (unsigned i = 0; i < children.size(); ++i)
	{
		getCovarianceHierarchy(center, covarianceMatrix);
	}

	rotationMatrix = calculateAxisMatrix(covarianceMatrix);

	rotationMatrix.invertRotation();
	lrbtnf.clear();
	getOrientedHierarchy(lrbtnf, rotationMatrix);
	rotationMatrix.invertRotation();
	orientedBox.init(lrbtnf, rotationMatrix);

	/******************************************************************************/

	for (unsigned i = 0; i < children.size(); ++i)
	{
		children[i]->calculateLocalOrientedBoxHierarchy();
	}
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
	// if (planes.inFrustum(sphere))
	// {
	if (planes.inFrustum(orientedBox))
	{
		// if (planes.inFrustum(orientedBox))
		// {
		// if (children.size() == 0 || planes.inFrustum(localSphere))
		// {
	// if (planes.inFrustum(box))
	// {
	// 	if (children.size() == 0 || planes.inFrustum(localBox))
	// 	{
			shaderProgram->setUniform ("uModelView", modelView.getTransform());
			shaderProgram->setUniform ("uNormalMatrix", normal);
			for (unsigned i = 0; i < meshes.size(); ++i)
			{
				if (meshes[i]->hasTexture())
				{
					shaderProgram->setUniform ("uHasTexture", meshes[i]->hasTexture());
					// std::cout << meshes[i]->textureFilePath << std::endl;
					textures[meshes[i]->textureFilePath]->bind();
					meshes[i]->draw();
					textures[meshes[i]->textureFilePath]->unbind();
				}
				else
				{
					meshes[i]->draw();
				}
			}
			sphereD.init(orientedBox);
			// sphereD.init(localBox);
			// sphereD.init(box);
			// sphereD.init(localSphere);
			// sphereD.init(sphere);
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
