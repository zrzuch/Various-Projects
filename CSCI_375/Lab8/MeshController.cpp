#include "MeshController.h"
#include <iostream>

MeshController::MeshController()
	: m_meshes()
	, m_indices()
	, m_activeMesh(0)
	, m_activeTransform(0)
{ }

MeshController::~MeshController()
{
	for (uint i = 0; i < numMesh(); ++i) 
	{
		delete getMesh(i);
	}
}

void
MeshController::add(const std::string& filename)
{
	int nameIndex = meshIndex(filename);
	if (nameIndex == -1)
	{
		add(filename, new Mesh(filename));
	}
	else
	{
		m_meshes[nameIndex].first->addCopy();
	}
}

void
MeshController::add (const std::string& meshName, Mesh* mesh)
{
	m_indices.emplace(meshName, m_meshes.size());
	m_meshes.emplace_back(mesh, true);
}

void
MeshController::setActiveToDraw(bool draw)
{
	setToDraw(m_activeMesh, draw);
}

void
MeshController::setToDraw(const std::string& meshName, bool draw)
{
	setToDraw(meshIndex(meshName), draw);
}

void
MeshController::setToDraw(int index, bool draw)
{
	m_meshes[index].second = draw;
}

void
MeshController::fillToDraw(bool draw)
{
	for (uint i = 0; i < numMesh(); ++i)
	{
		setToDraw(i, draw);
	}
}

void
MeshController::removeActive()
{
	remove(m_activeMesh);
}

void
MeshController::remove(const std::string& meshName)
{
	remove(meshIndex(meshName));
}

void
MeshController::remove(int index)
{
	delete getMesh(index);
	m_meshes.erase(m_meshes.begin() + index);
}

void
MeshController::removeAll()
{
	for (uint i = 0; i < numMesh(); ++i) 
	{
		delete getMesh(i);
	}
	m_meshes.erase(m_meshes.begin(), m_meshes.end());
}

void
MeshController::setActiveMesh (const std::string& meshName)
{
	int index = meshIndex(meshName);
	if (index > -1) 
	{
		m_activeMesh = static_cast<uint>(index);
	}
}

void
MeshController::setActiveMesh (uint index)
{
	if (index < m_meshes.size()) 
	{
		m_activeMesh = index;
	}
}

void
MeshController::setActiveTransform (uint index)
{
	if (!isEmpty())
	{
		if (index < getMesh(m_activeMesh)->numTransforms())
		{
			m_activeTransform = index;
		}
	}
}

void
MeshController::next()
{
	if (!isEmpty())
	{
		++m_activeTransform;
		if (m_activeTransform >= getMesh(m_activeMesh)->numTransforms())
		{
			m_activeTransform = 0;
			++m_activeMesh;
			if (m_activeMesh >= m_meshes.size())
			{
				m_activeMesh = 0;
			}
		}
	}
}

void
MeshController::prev()
{
	if (!isEmpty())
	{
		if (m_activeTransform > 0) 
		{
			--m_activeTransform;
		}
		else
		{
			if (m_activeMesh > 0) 
			{
				--m_activeMesh;
			}
			else 
			{
				m_activeMesh = m_meshes.size() - 1;
			}
			m_activeTransform = getMesh(m_activeMesh)->numTransforms() - 1;
		}
	}
}

Mesh*
MeshController::getActiveMesh() 
{
	return getMesh(m_activeMesh);
}

Transform&
MeshController::getActiveTransform()
{
	return getMesh(m_activeMesh)->getTransform(m_activeTransform);
}

Mesh*
MeshController::getMesh(int index)
{
	return m_meshes[index].first;
}

bool
MeshController::isDrawing(int index) const
{
	return m_meshes[index].second;
}

uint
MeshController::numMesh() const
{
	return m_meshes.size();
}

int
MeshController::meshIndex(const std::string& meshName)
{
	auto namePos = m_indices.find(meshName);
	if( namePos != m_indices.end())
	{
		return namePos->second;
	}
	return -1;
}

bool
MeshController::isEmpty() const
{
	return numMesh() == 0;
}

void
MeshController::printMeshInfo()
{
	std::cout << "\n" 
		<< "Number of Unique Meshes = " << numMesh()
		<< "\n";
	for (std::pair<std::string, uint> meshIndex : m_indices)
	{
		std::cout << "\tMesh Name = " << meshIndex.first
			<< "\n"
			<< "\t\t" << "Index = " << meshIndex.second
			<< "\n"
			<< "\t\t" << "Copies = " << getMesh(meshIndex.second)->numTransforms()
			<< "\n";
	}
	std::cout << std::endl;
}