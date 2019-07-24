#include "ModelController.h"
#include <iostream>

ModelController::ModelController()
	: m_models()
	, m_indices()
	, m_activeModel(0)
	, m_activeTransform(0)
{ }

ModelController::~ModelController()
{
	for (uint i = 0; i < numModel(); ++i)
	{
		delete getModel(i);
	}
}

void
ModelController::prepare()
{
	for (uint i = 0; i < numModel(); ++i)
	{
		getModel(i)->prepare();
	}
}

void
ModelController::draw(ShaderProgram* shaderProgram, const Camera& camera)
{
	shaderProgram->enable();
	draw(shaderProgram, camera, true);
	shaderProgram->disable();
}

void
ModelController::draw(ShaderProgram* shaderProgram, const Camera& camera, bool isShaderOn)
{
	for (std::pair<Model*, bool> modelPair : m_models)
	{
		if (modelPair.second)
		{
			modelPair.first->draw(shaderProgram, camera, true);
		}
	}
}

void
ModelController::add(const std::string& filename, const Transform& beginOrientation)
{
	int nameIndex = modelIndex(filename);
	if (nameIndex == -1)
	{
		add(filename, new Model(filename, beginOrientation));
	}
	else
	{
		m_models[nameIndex].first->addCopy();
	}
}

void
ModelController::add (const std::string& modelName, Model* model)
{
	m_indices.emplace(modelName, m_models.size());
	m_models.emplace_back(model, true);
}

void
ModelController::setActiveToDraw(bool draw)
{
	setToDraw(m_activeModel, draw);
}

void
ModelController::setToDraw(const std::string& modelName, bool draw)
{
	setToDraw(modelIndex(modelName), draw);
}

void
ModelController::setToDraw(int index, bool draw)
{
	m_models[index].second = draw;
}

void
ModelController::fillToDraw(bool draw)
{
	for (uint i = 0; i < numModel(); ++i)
	{
		setToDraw(i, draw);
	}
}

void
ModelController::removeActive()
{
	remove(m_activeModel);
}

void
ModelController::remove(const std::string& modelName)
{
	remove(static_cast<unsigned>(modelIndex(modelName)));
}

void
ModelController::remove(unsigned index)
{
	if (index < m_models.size())
	{
		Model* model = getModel(index);
		std::string modelName = model->name;
		auto iterator = m_indices.find(modelName);
		m_indices.erase(iterator);
		m_models.erase(m_models.begin() + index);
		for (unsigned i = 0; i < m_models.size(); ++i)
		{
			m_indices[getModel(i)->name] = i;
		}
		std::cout << "GETS HERE!" << std::endl;
		delete model;
	}
}

void
ModelController::removeAll()
{
	if (m_models.size() > 0)
	{
		for (uint i = 0; i < numModel(); ++i) 
		{
			delete getModel(i);
		}
		m_models.clear();
		m_indices.clear();
		m_activeModel = 0;
		m_activeTransform = 0;
	}
}

void
ModelController::setActiveModel (const std::string& modelName)
{
	int index = modelIndex(modelName);
	if (index > -1) 
	{
		m_activeModel = static_cast<uint>(index);
	}
}

void
ModelController::setActiveModel (uint index)
{
	if (index < m_models.size()) 
	{
		m_activeModel = index;
	}
}

void
ModelController::setActiveTransform (uint index)
{
	if (!isEmpty())
	{
		if (index < getModel(m_activeModel)->numTransforms())
		{
			m_activeTransform = index;
		}
	}
}

void
ModelController::next()
{
	if (!isEmpty())
	{
		++m_activeTransform;
		if (m_activeTransform >= getModel(m_activeModel)->numTransforms())
		{
			m_activeTransform = 0;
			++m_activeModel;
			if (m_activeModel >= m_models.size())
			{
				m_activeModel = 0;
			}
		}
	}
}

void
ModelController::prev()
{
	if (!isEmpty())
	{
		if (m_activeTransform > 0) 
		{
			--m_activeTransform;
		}
		else
		{
			if (m_activeModel > 0) 
			{
				--m_activeModel;
			}
			else 
			{
				m_activeModel = m_models.size() - 1;
			}
			m_activeTransform = getModel(m_activeModel)->numTransforms() - 1;
		}
	}
}

Model*
ModelController::getActiveModel() 
{
	return getModel(m_activeModel);
}

Transform&
ModelController::getActiveTransform()
{
	return getModel(m_activeModel)->getTransform(m_activeTransform);
}

Model*
ModelController::getModel(int index)
{
	return m_models[index].first;
}

Model*
ModelController::getModel(const std::string& modelName)
{
	int index = modelIndex(modelName);
	if (index > -1)
	{
		return m_models[index].first;
	}
	return nullptr;
}

bool
ModelController::isDrawing(int index) const
{
	return m_models[index].second;
}

uint
ModelController::numModel() const
{
	return m_models.size();
}

int
ModelController::modelIndex(const std::string& modelName)
{
	auto namePos = m_indices.find(modelName);
	if( namePos != m_indices.end())
	{
		return namePos->second;
	}
	return -1;
}

bool
ModelController::isEmpty() const
{
	return numModel() == 0;
}

void
ModelController::printModelInfo()
{
	std::cout << "\n" 
		<< "Number of Unique Models = " << numModel()
		<< "\n";
	for (std::pair<std::string, uint> modelIndex : m_indices)
	{
		std::cout << "\tModel Name = " << modelIndex.first
			<< "\n"
			<< "\t\t" << "Index    = " << modelIndex.second
			<< "\n"
			<< "\t\t" << "Copies   = " << getModel(modelIndex.second)->numTransforms()
			<< "\n"
			<< "\t\t" << "Indices  = " << getModel(modelIndex.second)->numIndices()
			<< "\n"
			<< "\t\t" << "Vertices = " << getModel(modelIndex.second)->numVertices()
			<< "\n";
	}
	std::cout << std::endl;
}