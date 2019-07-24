// AiScene class for importing Mesh data. 
// Author: Gary M. Zoppetti, Ph.D.

#ifndef AISCENE_H
#define AISCENE_H

#include <string>
#include <vector>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include "Matrix4.h"
#include "Transform.h"
#include "Animation.h"

// Make sure you add "-lassimp" to your Makefile!

class AiScene
{
public:
  AiScene (const std::string& fileName, const Transform& beginOrientation = Transform());

  // Nothing to do as Importer dtor cleans up!
  ~AiScene () = default;

  // Disable default copy ctor and copy assignment.
  AiScene (const AiScene&) = delete;
  AiScene& operator= (const AiScene&) = delete;

  aiNode*
  findModelRoot();

  bool
  inVector(const std::vector<aiString>& names, aiNode* node);

  aiNode*
  findFirst(const std::vector<aiString>& names, aiNode* node);

  Bone*
  getBones();

  Matrix4
  aiMatrixToMatrix4(const aiMatrix4x4& mat) const;

  Transform
  aiMatrixToTransform(const aiMatrix4x4& mat) const;

  Bone*
  recursiveNodeProcess(aiNode* node);

  Transform
  findBoneMatrix(aiString name);

  std::vector<Animation>
  getAnimations(aiString name);

  aiNodeAnim*
  findNodeAnim(aiAnimation* animation, aiString name);

  std::vector<float>
  getAllVertexData() const;

  std::vector<std::vector<float>>
  getAllVertexDataSeperate() const;

  std::vector<unsigned>
  getAllFaceIndices() const;

  std::vector<std::vector<unsigned>>
  getAllFaceIndicesSeperate() const;

  std::vector<std::string>
  getAllTexturePaths() const;

  std::vector<std::pair<std::vector<unsigned>, std::vector<float>>>
  getAllBoneData() const;

  // Read vertex data for mesh number "meshNum".
  // A scene may consist of multiple meshes. 
  std::vector<float>
  readVertexData (unsigned meshNum) const;

  std::pair<std::vector<unsigned>, std::vector<float>>
  getVertexBoneData (unsigned meshNum) const;

  std::vector<unsigned>
  getFaceIndices (unsigned meshNum) const;

  std::string
  getTextureFilePath(unsigned meshNum) const;

  // You may find other methods useful...
  
private:
  // Importer dtor destroys the scene!
  Assimp::Importer m_importer;
  Transform m_GlobalInverseTransform;
  static constexpr unsigned FLOATS_PER_VERTEX = 8;
};

#endif
