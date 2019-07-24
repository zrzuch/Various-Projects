// AiScene class for importing Mesh data. 
// Author: Gary M. Zoppetti, Ph.D.

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <assimp/postprocess.h>

#include "AiScene.h"

AiScene::AiScene (const std::string& fileName, const Transform& beginOrientation)
    : m_GlobalInverseTransform(beginOrientation)
{
    // Meshes may not consist of triangles, so have the importer
    //   triangulate.
    // Meshes may not have normals, so if they don't, have the importer
    //   generate them. 
    const aiScene* scene = m_importer.ReadFile(fileName, aiProcess_Triangulate 
        | aiProcess_GenSmoothNormals | aiProcess_FixInfacingNormals | aiProcess_JoinIdenticalVertices 
        | aiProcess_RemoveRedundantMaterials | aiProcess_ImproveCacheLocality | aiProcess_GenUVCoords 
        /*| aiProcess_OptimizeGraph | aiProcess_OptimizeMeshes*/ );
    if (scene == nullptr)
    {
        auto error = m_importer.GetErrorString ();
        fprintf (stderr, "Failed to load model %s with error '%s'. Exiting\n",
            fileName.c_str (), error);
        exit (-1);
    }
    Transform globalInverse = aiMatrixToTransform(scene->mRootNode->mTransformation);
    globalInverse.invert();
    m_GlobalInverseTransform.combine(globalInverse);
    
}

std::vector<float>
AiScene::getAllVertexData() const
{
    std::vector<float> vertexData;
    for (unsigned meshNum = 0; meshNum < m_importer.GetScene()->mNumMeshes; ++meshNum)
    {
        std::vector<float> meshVertexData = readVertexData( meshNum );
        vertexData.insert(vertexData.end(), meshVertexData.begin(), meshVertexData.end());
    }
    return vertexData;
}

std::vector<std::vector<float>>
AiScene::getAllVertexDataSeperate() const
{
    std::vector<std::vector<float>> vertexData;
    for (unsigned meshNum = 0; meshNum < m_importer.GetScene()->mNumMeshes; ++meshNum)
    {
        vertexData.push_back(readVertexData( meshNum ));
    }
    return vertexData;
}

std::vector<unsigned>
AiScene::getAllFaceIndices() const
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
        indices.insert(indices.end(), meshIndices.begin(), meshIndices.end());
        beginFaceIndex += m_importer.GetScene()->mMeshes[meshNum]->mNumVertices;
    }
    return indices;
}

std::vector<std::vector<unsigned>>
AiScene::getAllFaceIndicesSeperate() const
{
    std::vector<std::vector<unsigned>> indices;
    for (unsigned meshNum = 0; meshNum < m_importer.GetScene()->mNumMeshes; ++meshNum)
    {
        indices.push_back(getFaceIndices( meshNum ));
    }
    return indices;
}

std::vector<std::string>
AiScene::getAllTexturePaths()
{
    std::vector<std::string> filePaths;
    for (unsigned meshNum = 0; meshNum < m_importer.GetScene()->mNumMeshes; ++meshNum)
    {
        filePaths.push_back(getProperPath(getTextureFilePath(meshNum)));
    }
    return filePaths;
}

std::string
AiScene::getProperPath(std::string file)
{
    std::string fileName = file;
    size_t slash = fileName.find("//");
    while (slash != std::string::npos)
    {
        if (slash == 0)
        {
            fileName.erase(slash, 2);
        }
        else
        {
            fileName.replace(slash, 2, "/");
        }
        slash = fileName.find("//");
    }

    slash = fileName.find("\\");
    while (slash != std::string::npos)
    {
        if (slash == 0)
        {
            fileName.erase(slash, 1);
        }
        else
        {
            fileName.replace(slash, 1, "/");
        }
        slash = fileName.find("\\");
    }

    slash = fileName.find("/");
    if (slash == 0)
    {
        fileName.erase(slash, 1);
    }

    return fileName;
}

std::vector<std::pair<std::vector<unsigned>, std::vector<float>>>
AiScene::getAllBoneData() const
{
    std::vector<std::pair<std::vector<unsigned>, std::vector<float>>> bones;
    if (m_importer.GetScene()->mNumAnimations == 0)
    {
        return bones;
    }

    unsigned meshSize = m_importer.GetScene()->mNumMeshes;
    bones.reserve(meshSize);

    for (unsigned meshNum = 0; meshNum < meshSize; ++meshNum)
    {
        bones.push_back(getVertexBoneData(meshNum));
    }
    return bones;
}

std::vector<float>
AiScene::readVertexData (unsigned meshNum) const
{
    // Get the correct mesh object
    const aiMesh* mesh = m_importer.GetScene()->mMeshes[meshNum];
    //std::cout << mesh->mNumBones << std::endl;
    // Container for holding vertex data
    std::vector<float> vertexData;
    vertexData.reserve(mesh->mNumVertices * FLOATS_PER_VERTEX);
    // Go through array of vertices and normals
    for (unsigned vertexNum = 0; vertexNum < mesh->mNumVertices; ++vertexNum)
    {
        // TODO: Put the position in vertexData
        aiVector3D position = mesh->mVertices[vertexNum];
        vertexData.push_back(position.x);
        vertexData.push_back(position.y);
        vertexData.push_back(position.z);
        // TODO: Put the normal in vertexData
        aiVector3D normal = mesh->mNormals[vertexNum];
        vertexData.push_back(normal.x);
        vertexData.push_back(normal.y);
        vertexData.push_back(normal.z);
        // TODO: Put the texture coordinate in vertexData
        if (mesh->mTextureCoords[0] != nullptr)
        {
            aiVector3D textureCoord = mesh->mTextureCoords[0][vertexNum];
            vertexData.push_back(textureCoord.x);
            vertexData.push_back(textureCoord.y);
        }
        else
        {
            vertexData.push_back(0);
            vertexData.push_back(0);
        }

    }
    return vertexData;
}

bool
AiScene::inVector(const std::vector<aiString>& names, aiNode* node)
{
    for (aiString name : names)
    {
        if (name == node->mName)
        {
            return true;
        }
    }
    return false;
}

Bone*
AiScene::getBones()
{
    if (m_importer.GetScene()->mNumAnimations == 0)
    {
        return nullptr;
    }
    return recursiveNodeProcess(findModelRoot());
}

bool
AiScene::isMeshHierarchy(aiNode* node)
{
    if (node == nullptr)
    {
        return false;
    }
    if (node->mNumChildren == 0)
    {
        return false;
    }
    for (unsigned i = 0; i < node->mNumChildren; ++i)
    {
        if (node->mChildren[i]->mNumMeshes > 0)
        {
            return true;
        }
    }
    return false;
}


MeshNode*
AiScene::getMeshHierarchy()
{
    aiNode* meshRoot = findFirstMesh(m_importer.GetScene()->mRootNode);
    //std::cout << "Number of Meshes = " << m_importer.GetScene()->mNumMeshes << std::endl;
    if (isMeshHierarchy(meshRoot))
    {
        return getMeshNode(meshRoot);
    }
    else
    {
        return new MeshNode(getAllVertexDataSeperate(), 
                            getAllFaceIndicesSeperate(), 
                            getAllTexturePaths(), 
                            getAllBoneData());
    }
}

aiNode*
AiScene::findFirstMesh(aiNode* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else if (node->mNumMeshes > 0)
    {
        return node;
    }
    else
    {
        for (unsigned i = 0; i < node->mNumChildren; ++i)
        {
            aiNode* child = findFirstMesh(node->mChildren[i]);
            if (child != nullptr)
            {
                return child;
            }
        }
    }
    return nullptr;
}

// Get the Mesh Hierarchy
// Make sure node is not nullptr
MeshNode*
AiScene::getMeshNode(aiNode* node)
{
    std::vector<std::pair<std::vector<unsigned>, std::vector<float>>> boneData;
    std::vector<std::vector<float>> vertexData;  
    std::vector<std::vector<unsigned>> indices;
    std::vector<std::string> texturePaths;

    // std::cout << "Meshes Per Node = " << node->mNumMeshes << std::endl;
    
    for (unsigned i = 0; i < node->mNumMeshes; ++i)
    {
        texturePaths.push_back(getTextureFilePath(node->mMeshes[i]));
        vertexData.push_back(readVertexData(node->mMeshes[i]));
        indices.push_back(getFaceIndices(node->mMeshes[i]));
    }
    if (m_importer.GetScene()->mNumAnimations > 0)
    {
        for (unsigned i = 0; i < node->mNumMeshes; ++i)
        {
            boneData.push_back(getVertexBoneData(node->mMeshes[i]));
        }
    }

    MeshNode* meshNode = new MeshNode(vertexData, indices, texturePaths, boneData);

    for (unsigned nodeNum = 0; nodeNum < node->mNumChildren; ++nodeNum)
    {
        meshNode->children.push_back(getMeshNode(node->mChildren[nodeNum]));
    }
    return meshNode;
}

aiNode*
AiScene::findModelRoot()
{
    unsigned meshSize = m_importer.GetScene()->mNumMeshes;

    std::vector<aiString> names;
    names.reserve(meshSize);

    for (unsigned meshNum = 0; meshNum < meshSize; ++meshNum)
    {
        // Mesh Bone Root Shares Name with model root
        //  confirmed in documentation
        names.push_back(m_importer.GetScene()->mMeshes[meshNum]->mBones[0]->mName);
    }

    return findFirst(names, m_importer.GetScene()->mRootNode);
}

aiNode*
AiScene::findFirst(const std::vector<aiString>& names, aiNode* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (inVector(names, node))
    {
        return node;
    }

    for(unsigned i = 0; i < node->mNumChildren; i++)
    {
        aiNode* child = findFirst(names, node->mChildren[i]);
        if (child != nullptr)
        {
            return child;
        }
    }
    return nullptr;
}

int
AiScene::findMesh(aiString name)
{
    for (unsigned i = 0; i < m_importer.GetScene()->mNumMeshes; ++i)
    {
        if (m_importer.GetScene()->mMeshes[i]->mName == name)
        {
            return i;
        }
    }
    return -1;
}

Bone*
AiScene::recursiveNodeProcess(aiNode* node)
{
    std::string name(node->mName.C_Str());
    Bone* currBone = new Bone(name
                            , findBoneMatrix(node->mName)
                            , m_GlobalInverseTransform
                            , aiMatrixToTransform(node->mTransformation));
    currBone->animations = getAnimations(node->mName);

    for(unsigned i = 0; i < node->mNumChildren; i++)
    {
        currBone->addChild(recursiveNodeProcess(node->mChildren[i]));
    }

    return currBone;
}

std::vector<Animation>
AiScene::getAnimations(aiString name)
{
    const aiScene* scene = m_importer.GetScene();
    unsigned numAnimations = scene->mNumAnimations;
    std::vector<Animation> animations;
    animations.reserve(numAnimations);

    for (unsigned i = 0; i < numAnimations; ++i)
    {
        aiNodeAnim* node = findNodeAnim(scene->mAnimations[i], name);
        if (node != nullptr)
        {
            Animation animation;
            animation.name = std::string(scene->mAnimations[i]->mName.C_Str());
            animation.duration = scene->mAnimations[i]->mDuration;
            animation.ticksPerSecond = scene->mAnimations[i]->mTicksPerSecond;

            animation.positions.reserve(node->mNumPositionKeys);
            for (unsigned i = 0; i < node->mNumPositionKeys; ++i)
            {
                float x = node->mPositionKeys[i].mValue.x;
                float y = node->mPositionKeys[i].mValue.y;
                float z = node->mPositionKeys[i].mValue.z;
                float timeStamp = node->mPositionKeys[i].mTime;
                animation.positions.push_back(Vector3Key(Vector3(x, y, z), timeStamp));
            }

            animation.rotations.reserve(node->mNumRotationKeys);
            for (unsigned i = 0; i < node->mNumRotationKeys; ++i)
            {
                float x = node->mRotationKeys[i].mValue.x;
                float y = node->mRotationKeys[i].mValue.y;
                float z = node->mRotationKeys[i].mValue.z;
                float w = node->mRotationKeys[i].mValue.w;
                float timeStamp = node->mRotationKeys[i].mTime;
                animation.rotations.push_back(QuaternionKey(Quaternion(x, y, z, w), timeStamp));
            }

            animation.scalings.reserve(node->mNumScalingKeys);
            for (unsigned i = 0; i < node->mNumScalingKeys; ++i)
            {
                float x = node->mScalingKeys[i].mValue.x;
                float y = node->mScalingKeys[i].mValue.y;
                float z = node->mScalingKeys[i].mValue.z;
                float timeStamp = node->mScalingKeys[i].mTime;
                animation.scalings.push_back(Vector3Key(Vector3(x, y, z), timeStamp));
            }
            animations.push_back(animation);
        }
    }
    return animations;
}

aiNodeAnim*
AiScene::findNodeAnim(aiAnimation* animation, aiString name)
{
    for (unsigned i = 0; i < animation->mNumChannels; ++i)
    {
        // return if node animation name matches name given
        if (animation->mChannels[i]->mNodeName == name)
        {
            return animation->mChannels[i];
        }
    }
    return nullptr;
}

Transform
AiScene::findBoneMatrix(aiString name)
{
    const aiScene* scene = m_importer.GetScene();
    aiMesh* mesh;
    aiBone* bone;
    for (unsigned meshNum = 0; meshNum < scene->mNumMeshes; ++meshNum)
    {
        mesh = scene->mMeshes[meshNum];
        for (unsigned boneNum = 0; boneNum < mesh->mNumBones; ++boneNum)
        {
            bone = mesh->mBones[boneNum];
            if (bone->mName == name)
            {
                return aiMatrixToTransform(bone->mOffsetMatrix);
            }
        }
    }
    return Transform();
}

std::pair<std::vector<unsigned>, std::vector<float>>
AiScene::getVertexBoneData (unsigned meshNum) const
{
    // Modern Game Engines use 4 WEIGHTS_PER_VERTEX and then changes the shader 
    //      to allow a max of 8 WEIGHTS_PER_VERTEX but they recommend against it.
    constexpr unsigned WEIGHTS_PER_VERTEX = 3;
    const aiMesh* mesh = m_importer.GetScene()->mMeshes[meshNum];

    std::vector<unsigned> boneIDs(mesh->mNumVertices * WEIGHTS_PER_VERTEX);
    std::vector<float> boneWeights(mesh->mNumVertices * WEIGHTS_PER_VERTEX);
    
    for (unsigned i = 0; i < mesh->mNumBones; ++i)
    {
        aiBone* bone = mesh->mBones[i];
        std::string name(bone->mName.C_Str());

        for(unsigned j = 0; j < bone->mNumWeights; j++)
        {
            aiVertexWeight weight = bone->mWeights[j];
            unsigned vertexStart = weight.mVertexId * WEIGHTS_PER_VERTEX;
            for(unsigned k = 0; k < WEIGHTS_PER_VERTEX; k++)
            {
                if(boneWeights[vertexStart + k] < weight.mWeight)
                {
                    boneIDs[vertexStart + k] = i;
                    boneWeights[vertexStart + k] = weight.mWeight;
                    break;
                }
            }
        }
    }
    return std::pair<std::vector<unsigned>, std::vector<float>>(boneIDs, boneWeights);
}

Matrix4
AiScene::aiMatrixToMatrix4(const aiMatrix4x4& mat) const
{
    return Matrix4 
    (
        mat.a1, mat.b1, mat.c1, mat.d1, 
        mat.a2, mat.b2, mat.c2, mat.d2,
        mat.a3, mat.b3, mat.c3, mat.d3, 
        mat.a4, mat.b4, mat.c4, mat.d4
    );
}

Transform
AiScene::aiMatrixToTransform(const aiMatrix4x4& mat) const
{
    Vector3 position(mat.a4, mat.b4, mat.c4);
    Matrix3 m
    (
        mat.a1, mat.b1, mat.c1,
        mat.a2, mat.b2, mat.c2,
        mat.a3, mat.b3, mat.c3
    );
    return Transform(position, m);
}

std::vector<unsigned>
AiScene::getFaceIndices (unsigned meshNum) const
{
    const aiMesh* mesh = m_importer.GetScene()->mMeshes[meshNum];
    constexpr unsigned INDICES_PER_FACE = 3;
    std::vector<unsigned> indices;
    indices.reserve(mesh->mNumFaces * INDICES_PER_FACE);

    for (unsigned faceNum = 0; faceNum < mesh->mNumFaces; ++faceNum)
    {
        const aiFace& face = mesh->mFaces[faceNum];
        for (unsigned indexNum = 0; indexNum < INDICES_PER_FACE; ++indexNum)
        {
            indices.push_back(face.mIndices[indexNum]);
        }
    }
    return indices;
}

std::string
AiScene::getTextureFilePath(unsigned meshNum)
{
    const unsigned matIndex = m_importer.GetScene()->mMeshes[meshNum]->mMaterialIndex;
    const aiMaterial* material = m_importer.GetScene()->mMaterials[matIndex];
    if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString path;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
        {
            return std::string(path.C_Str());
        }
    }
    return "";
}

void
AiScene::printNodeHierarchy(aiNode* node)
{
    std::cout << node->mName.C_Str() << std::endl;
    for (unsigned i = 0; i < node->mNumChildren; ++i)
    {
        printNodeHierarchy(node->mChildren[i]);
    }
}