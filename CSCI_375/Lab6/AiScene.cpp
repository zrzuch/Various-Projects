// AiScene class for importing Mesh data. 
// Author: Gary M. Zoppetti, Ph.D.

#include <cstdio>
#include <cstdlib>

#include <assimp/postprocess.h>

#include "AiScene.h"

AiScene::AiScene (const std::string& fileName)
{
  // Meshes may not consist of triangles, so have the importer
  //   triangulate.
  // Meshes may not have normals, so if they don't, have the importer
  //   generate them. 
  const aiScene* m_scene = m_importer.ReadFile(fileName, 
    aiProcess_Triangulate | aiProcess_GenSmoothNormals);
  if (m_scene == nullptr)
  {
    auto error = m_importer.GetErrorString ();
    fprintf (stderr, "Failed to load model %s with error '%s'. Exiting\n",
	     fileName.c_str (), error);
    exit (-1);
  }
}

std::vector<float>
AiScene::getAllVertexData()
{
  std::vector<float> vertexData;
  for (unsigned meshNum = 0; meshNum < m_importer.GetScene()->mNumMeshes; ++meshNum)
  {
    std::vector<float> meshVertexData = readVertexData( meshNum );
    vertexData.insert(vertexData.end(), meshVertexData.begin(), 
      meshVertexData.end());
  }
  return vertexData;
}

std::vector<unsigned>
AiScene::getAllFaceIndices()
{
  std::vector<unsigned> indices;
  unsigned beginFaceIndex = 0;
  for (unsigned meshNum = 0; meshNum < m_importer.GetScene()->mNumMeshes; ++meshNum)
  {
    std::vector<unsigned> meshIndices = getFaceIndices( meshNum );

    for (unsigned i = 0; i < meshIndices.size(); ++i)
    {
      meshIndices[i] += beginFaceIndex;
    } 

    indices.insert(indices.end(), meshIndices.begin(), 
      meshIndices.end());
    beginFaceIndex += m_importer.GetScene()->mMeshes[meshNum]->mNumVertices;
  }
  return indices;
}

std::vector<float>
AiScene::readDuplicateVertexData (unsigned meshNum) const
{
  // Get the correct mesh object
  const aiMesh* mesh = m_importer.GetScene()->mMeshes[meshNum];
  const unsigned INDICES_PER_FACE = 3;
  // Container for holding vertex data
  std::vector<float> vertexData(mesh->mNumFaces* INDICES_PER_FACE* FLOATS_PER_VERTEX);
  
  // Go through array of faces
  for (unsigned faceNum = 0; faceNum < mesh->mNumFaces; ++faceNum)
  {
    // Get a face
    const aiFace& face = mesh->mFaces[faceNum];
    // Faces are triangles, so three indices
    // Go through the 3 indices
    for (unsigned indexNum = 0; indexNum < INDICES_PER_FACE; ++indexNum)
    {
      // Get vertex number at location "indexNum"
      // Indexing is used so data isn't duplicated
      auto vertexNum = face.mIndices[indexNum];
      // TODO: Put the position in vertexData
      aiVector3D position = mesh->mVertices[vertexNum];
      vertexData[faceNum * indexNum * FLOATS_PER_VERTEX    ] = position.x;
      vertexData[faceNum * indexNum * FLOATS_PER_VERTEX + 1] = position.y;
      vertexData[faceNum * indexNum * FLOATS_PER_VERTEX + 2] = position.z;
      // TODO: Put the normal in vertexData
      aiVector3D normal = mesh->mNormals[vertexNum];
      vertexData[faceNum * indexNum * FLOATS_PER_VERTEX + 3] = normal.x;
      vertexData[faceNum * indexNum * FLOATS_PER_VERTEX + 4] = normal.y;
      vertexData[faceNum * indexNum * FLOATS_PER_VERTEX + 5] = normal.z;
    }
  }
  return vertexData;
}

std::vector<float>
AiScene::readVertexData (unsigned meshNum) const
{
  // Get the correct mesh object
  const aiMesh* mesh = m_importer.GetScene()->mMeshes[meshNum];
  // Container for holding vertex data
  std::vector<float> vertexData(mesh->mNumVertices * FLOATS_PER_VERTEX);
  
  // Go through array of vertices and normals
  for (unsigned vertexNum = 0; vertexNum < mesh->mNumVertices; ++vertexNum)
  {
      // TODO: Put the position in vertexData
      aiVector3D position = mesh->mVertices[vertexNum];
      vertexData[vertexNum * FLOATS_PER_VERTEX    ] = position.x;
      vertexData[vertexNum * FLOATS_PER_VERTEX + 1] = position.y;
      vertexData[vertexNum * FLOATS_PER_VERTEX + 2] = position.z;
      // TODO: Put the normal in vertexData
      aiVector3D normal = mesh->mNormals[vertexNum];
      vertexData[vertexNum * FLOATS_PER_VERTEX + 3] = normal.x;
      vertexData[vertexNum * FLOATS_PER_VERTEX + 4] = normal.y;
      vertexData[vertexNum * FLOATS_PER_VERTEX + 5] = normal.z;
  }
  return vertexData;
}

std::vector<unsigned>
AiScene::getFaceIndices (unsigned meshNum) const
{
  const aiMesh* mesh = m_importer.GetScene()->mMeshes[meshNum];

  const unsigned INDICES_PER_FACE = 3;

  std::vector<unsigned> indices(mesh->mNumFaces * INDICES_PER_FACE);

  for (unsigned faceNum = 0; faceNum < mesh->mNumFaces; ++faceNum)
  {
    const aiFace& face = mesh->mFaces[faceNum];
    for (unsigned indexNum = 0; indexNum < INDICES_PER_FACE; ++indexNum)
    {
      indices[faceNum * 3 + indexNum] = face.mIndices[indexNum];
    }
  }
  return indices;
}
