#ifndef ModelCONTROLLER_H
#define ModelCONTROLLER_H

#include <utility>
#include "Model.h"

class ModelController
{
public:
	ModelController();

	~ModelController();

	// Disable default copy ctor and copy assignment
  	ModelController (const ModelController&) = delete;
  	ModelController& operator= (const ModelController&) = delete;

  	void
  	prepare();

  	void
  	draw(ShaderProgram* shaderProgram, const Camera& camera);

  	void
  	draw(ShaderProgram* shaderProgram, const Camera& camera, bool isShaderOn);

	void
	add(const std::string& filename, const Transform& beginOrientation = Transform());

	// User must ensure no copies are made
	void
	add (const std::string& modelName, Model* model);

	void
	setActiveToDraw(bool draw = true);

	void
	setToDraw(const std::string& modelName, bool draw = true);

	void
	setToDraw(int index, bool draw = true);

	void
	fillToDraw(bool draw = true);

	void
	removeActive();

	void
	remove(const std::string& modelName);

	void
	remove(unsigned index);

	void
	removeAll();

	void
	setActiveModel (const std::string& modelName);

	void
	setActiveModel (unsigned index);

	void
	setActiveTransform (unsigned index);

	void
	next();

	void
	prev();
	
	Model*
	getActiveModel ();

	Transform&
	getActiveTransform ();

	Model*
	getModel(int index);

	Model*
	getModel(const std::string& modelName);

	bool
	isDrawing(int index) const;

	uint
	numModel() const;

	int
	modelIndex(const std::string& modelName);
	
	bool
	isEmpty() const;

	void
	printModelInfo();

private:
	//	Overhead is 4 bytes per unique Model and the vector overhead.
	std::vector<std::pair<Model*, bool>> m_models;
	std::unordered_map<std::string, unsigned> m_indices;

	unsigned m_activeModel;
	unsigned m_activeTransform;
};

#endif