#pragma once

#include "Frustum.h"
#include "Mesh.h"
#include <gsl/gsl_eigen.h>
#include "Math.h"

struct BSPNode
{
	Plane 		splitter;
	Mesh* 		polygons;
	// parent added for iterative traversal
	// will be added later
	// BSPNode* 	parent;
	BSPNode* 	front;
	BSPNode* 	back;

	// init node constructor
	BSPNode(Mesh* polygonList = nullptr, /*BSPNode* nodeParent = nullptr,*/ BSPNode* nodeFront = nullptr, BSPNode* nodeBack = nullptr)
	: polygons(polygonList)
	// , parent(nodeParent)
	, front(nodeFront)
	, back(nodeBack)
	{ }

	~BSPNode()
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
	calculateSplitter()
	{
		// Mean/Centroid and Covariance matrix calculations
		Vector3 centroid = polygons.getMeshCenter();
		Matrix3 covariance = polygons.getCovarianceMatrix(centroid);

		// setup for gsl library
		// gsl is a c function library so pointers 
		//	must be allocated and destroyed will explicit calls
		constexpr unsigned MATRIX_ROW_MAX = 3;
		gsl_eigen_symmv_workspace* w = gsl_eigen_symmv_alloc(MATRIX_ROW_MAX);
		gsl_matrix* cov = gsl_matrix_calloc(MATRIX_ROW_MAX,MATRIX_ROW_MAX);
		for (unsigned i = 0; i < MATRIX_ROW_MAX; ++i)
		{
			for (unsigned j = 0; j < MATRIX_ROW_MAX; ++j)
			{
				gsl_matrix_set(cov, i, j, covariance.getValue(i,j));
			}
		}
		gsl_vector* eval = gsl_vector_calloc(MATRIX_ROW_MAX);
		gsl_matrix* evec = gsl_matrix_calloc(MATRIX_ROW_MAX);

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
		bool is0GreaterThan1 = eigenValues[0] > eigenValues[1];
		Vector3 splitNormal;
		// 0 is the greatest
		if ( is0GreaterThan1 && eigenValues[0] > eigenValues[2] )
		{
			splitNormal = 
			{
				gsl_matrix_get(evec, 0, 0),
				gsl_matrix_get(evec, 1, 0),
				gsl_matrix_get(evec, 2, 0)
			};
		}
		// 1 is the greatest
		else if ( !is0GreaterThan1 && eigenValues[1] > eigenValues[2])
		{
			splitNormal = 
			{
				gsl_matrix_get(evec, 0, 1),
				gsl_matrix_get(evec, 1, 1),
				gsl_matrix_get(evec, 2, 1)
			};
		}
		// 2 is the greatest
		else
		{
			splitNormal = 
			{
				gsl_matrix_get(evec, 0, 2),
				gsl_matrix_get(evec, 1, 2),
				gsl_matrix_get(evec, 2, 2)
			};
		}
		gsl_matrix_free(evec);
		splitter = { splitNormal.x, splitNormal.y, splitNormal.z, -( splitNormal.dot( centroid ))};
	}
};

class BSPTree
{
public:
	
	BSPTree(Mesh* polygonList)
	: root(polygonList)
	{
		buildTree(root);
	}

	~BSPTree()
	{
		delete root;
	}

	void
	prepare()
	{
		prepare(root);
	}

private:

	void
	buildTree(BSPNode* node)
	{
		if (node == nullptr)
		{
			return;
		}

		constexpr unsigned INDICES_PER_TRIANGLE = 3;
		constexpr unsigned MAX_POLYGONS_PER_NODE = 10;
		unsigned numPolygons = node->polygonList->numIndices() / INDICES_PER_TRIANGLE;
		if (numPolygons <= MAX_POLYGONS_PER_NODE)
		{
			return;
		}

		node->calculateSplitter();
		std::pair<Mesh*, Mesh*> splitMeshes = node->polygonList->split(node->splitter);

		delete node->polygonList;
		node->polygonList = nullptr;

		node->front = new BSPNode(splitMeshes.first);
		buildTree(node->front);

		node->back = new BSPNode(splitMeshes.second);
		buildTree(node->back);
	}

	void
	prepare(BSPNode* node)
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

	BSPNode* root;
};