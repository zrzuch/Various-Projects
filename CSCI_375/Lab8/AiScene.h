// AiScene class for importing Mesh data. 
// Author: Gary M. Zoppetti, Ph.D.

#ifndef AISCENE_H
#define AISCENE_H

#include <string>
#include <vector>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

// Make sure you add "-lassimp" to your Makefile!

class AiScene
{
public:
  AiScene (const std::string& fileName);

  // Nothing to do as Importer dtor cleans up!
  ~AiScene () = default;

  // Disable default copy ctor and copy assignment.
  AiScene (const AiScene&) = delete;
  AiScene& operator= (const AiScene&) = delete;

  std::vector<float>
  getAllVertexData();

  std::vector<unsigned>
  getAllFaceIndices();

  std::vector<float>
  readDuplicateVertexData (unsigned meshNum) const;

  // Read vertex data for mesh number "meshNum".
  // A scene may consist of multiple meshes. 
  std::vector<float>
  readVertexData (unsigned meshNum) const;

  std::vector<unsigned>
  getFaceIndices (unsigned meshNum) const;

  // You may find other methods useful...
  
private:
  // Importer dtor destroys the scene!
  Assimp::Importer m_importer;
  const static unsigned FLOATS_PER_VERTEX = 6;
};

#endif
