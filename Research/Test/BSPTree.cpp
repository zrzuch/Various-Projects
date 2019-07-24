#include <gsl/gsl_eigen.h>
#include "Math.h"
#include "BSPTree.h"
#include "Material.h"

// init node constructor
BSPNode::BSPNode(Mesh* polygonList, /*BSPNode* nodeParent,*/ BSPNode* nodeFront, BSPNode* nodeBack)
: polygons(polygonList)
// , parent(nodeParent)
, front(nodeFront)
, back(nodeBack)
{ }

BSPNode::~BSPNode()
{
	if (polygons != nullptr)
	{
		delete polygons;
	}

	if (front != nullptr)
	{
		delete front;
	}

	if (back != nullptr)
	{
		delete back;
	}
}

void
BSPNode::calculateSplitter()
{
	// Mean/Centroid and Covariance matrix calculations
	Vector3 centroid = polygons->getMeshCenter();
	Matrix3 covariance;
	covariance.setToZero();
	polygons->getCovarianceMatrix(centroid, covariance);

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
			gsl_matrix_set(cov, i, j, covariance.getValue(i,j));
		}
	}
	gsl_vector* eval = gsl_vector_calloc(MATRIX_ROW_MAX);
	gsl_matrix* evec = gsl_matrix_calloc(MATRIX_ROW_MAX, MATRIX_ROW_MAX);

	// gsl eigen call for real symmetric matrix which a covariance of primitve positions is
	gsl_eigen_symmv(cov, eval, evec, w);
	gsl_matrix_free(cov);
	gsl_eigen_symmv_free(w);

	std::vector<double> eigenValues =
	{
		gsl_vector_get(eval, 0),
		gsl_vector_get(eval, 1),
		gsl_vector_get(eval, 2)
	};
	gsl_vector_free(eval);

	// largest eigen value will create a normal that points in the direction of the most variance
	//	which means better subdivison

	unsigned greatestEigenValue = ( eigenValues[0] > eigenValues[1] ) ? 0 : 1;
	greatestEigenValue = ( eigenValues[ greatestEigenValue ] > eigenValues[1] ) ? greatestEigenValue : 2;

	Vector3 splitNormal = 
	{
		static_cast<float>( gsl_matrix_get( evec, 0, greatestEigenValue )),
		static_cast<float>( gsl_matrix_get( evec, 1, greatestEigenValue )),
		static_cast<float>( gsl_matrix_get( evec, 2, greatestEigenValue ))
	};
	gsl_matrix_free(evec);
	splitter = { splitNormal.x, splitNormal.y, splitNormal.z, -( splitNormal.dot( centroid ))};
}

void
BSPNode::initBox()
{
	if (polygons == nullptr) return;

	std::vector<float> lrbtnf;
	polygons->getBoxBV(lrbtnf);
	box.init(lrbtnf);
}

BSPTree::BSPTree(Mesh* polygonList)
: root(new BSPNode(polygonList))
{
	buildTree(root);
	prepare();
	initBoxes();
}

BSPTree::~BSPTree()
{
	delete root;
}

void
BSPTree::prepare()
{
	prepare(root);
}

void
BSPTree::initBoxes()
{
	initBoxes(root);
}

void
BSPTree::buildTree(BSPNode* node)
{
	if (node == nullptr)
	{
		return;
	}

	constexpr unsigned INDICES_PER_TRIANGLE = 3;
	constexpr unsigned MAX_POLYGONS_PER_NODE = 600;
	unsigned numPolygons = node->polygons->numIndices() / INDICES_PER_TRIANGLE;
	if (numPolygons <= MAX_POLYGONS_PER_NODE)
	{
		return;
	}

	std::cout << "SPLIT" << std::endl;

	node->calculateSplitter();
	std::pair<Mesh*, Mesh*> splitMeshes = node->polygons->split(node->splitter);

	delete node->polygons;
	node->polygons = nullptr;

	node->front = new BSPNode(splitMeshes.first);
	buildTree(node->front);

	node->back = new BSPNode(splitMeshes.second);
	buildTree(node->back);
}

bool
BSPTree::isFront(const Vector3& position, BSPNode* node)
{
	if (node->splitter.dist(position) >= 0)
	{
		return true;
	}
	return false;
}

void
BSPTree::draw(ShaderProgram* shaderProgram, const Camera& camera, Transform& modelView, SphereDebug& sphereD)
{
	draw(shaderProgram, camera, modelView, sphereD, root);
}

void
BSPTree::draw(ShaderProgram* shaderProgram, const Camera& camera, Transform& modelView, SphereDebug& sphereD, BSPNode* node)
{
	if (node == nullptr) return;

	if (isFront(camera.getPosition(), node))
	{
		draw(shaderProgram, camera, modelView, sphereD, node->back);
		
		if (node->polygons != nullptr)
		{
			node->polygons->draw();
			sphereD.init(node->box);
			sphereD.draw(shaderProgram, modelView);
		}

		draw(shaderProgram, camera, modelView, sphereD, node->front);
	}
	else
	{
		draw(shaderProgram, camera, modelView, sphereD, node->front);

		if (node->polygons != nullptr)
		{
			node->polygons->draw();
			sphereD.init(node->box);
			sphereD.draw(shaderProgram, modelView);
		}

		draw(shaderProgram, camera, modelView, sphereD, node->back);
	}
}

void
BSPTree::initBoxes(BSPNode* node)
{
	if (node == nullptr) return;

	node->initBox();

	initBoxes(node->front);

	initBoxes(node->back);
}

void
BSPTree::prepare(BSPNode* node)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->polygons != nullptr)
	{
		node->polygons->prepareVao();
	}

	if (node->front != nullptr)
	{
		prepare(node->front);
	}

	if (node->back != nullptr)
	{
		prepare(node->back);
	}
}