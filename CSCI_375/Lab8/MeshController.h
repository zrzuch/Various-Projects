#ifndef MESHCONTROLLER_H
#define MESHCONTROLLER_H

#include <utility>
#include <map>
#include "Mesh.h"

class MeshController
{
public:
	MeshController();

	~MeshController();

	// Disable default copy ctor and copy assignment
  	MeshController (const MeshController&) = delete;
  	MeshController& operator= (const MeshController&) = delete;

	void
	add(const std::string& filename);

	// User must ensure no copies are made
	void
	add (const std::string& meshName, Mesh* mesh);

	void
	setActiveToDraw(bool draw = true);

	void
	setToDraw(const std::string& meshName, bool draw = true);

	void
	setToDraw(int index, bool draw = true);

	void
	fillToDraw(bool draw = true);

	void
	removeActive();

	void
	remove(const std::string& meshName);

	void
	remove(int index);

	void
	removeAll();

	void
	setActiveMesh (const std::string& meshName);

	void
	setActiveMesh (unsigned index);

	void
	setActiveTransform (unsigned index);

	void
	next();

	void
	prev();
	
	Mesh*
	getActiveMesh ();

	Transform&
	getActiveTransform ();

	Mesh*
	getMesh(int index);

	bool
	isDrawing(int index) const;

	uint
	numMesh() const;

	int
	meshIndex(const std::string& meshName);
	
	bool
	isEmpty() const;

	void
	printMeshInfo();

private:
	// Vector will preserve order. Map will allow for logN searching.
	//	Overhead is 4 bytes per unique mesh and the vector overhead.
	std::vector<std::pair<Mesh*, bool>> m_meshes;
	std::map<std::string, uint> m_indices;

	uint m_activeMesh;
	uint m_activeTransform;
};

#endif