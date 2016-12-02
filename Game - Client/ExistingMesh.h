/*

Copyright 2011 Etay Meiri

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OGLDEV_SKINNED_MESH_H
#define	OGLDEV_SKINNED_MESH_H

#include <map>
#include <vector>
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"   

#include "Graphics_Header.h"
//#include "ogldev_util.h"
//#include "ogldev_math_3d.h"
//#include "ogldev_texture.h"

using namespace std;
using namespace glm;

class SkinnedMesh
{
public:
	SkinnedMesh();

	~SkinnedMesh();

	bool LoadMesh(const string& Filename);

	void Render();

	GLuint NumBones() const
	{
		return m_NumBones;
	}

	void BoneTransform(float TimeInSeconds, vector<mat4>& Transforms);

private:
#define NUM_BONES_PER_VEREX 4

	struct BoneInfo
	{
		mat4 BoneOffset;
		mat4 FinalTransformation;

		BoneInfo()
		{
			BoneOffset = mat4();
			FinalTransformation = mat4();
		}
	};

	struct VertexBoneData
	{
		uint IDs[NUM_BONES_PER_VEREX];
		float Weights[NUM_BONES_PER_VEREX];


		void AddBoneData(uint BoneID, float Weight);
	};

	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	uint FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
	uint FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
	uint FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
	const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName);
	void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const mat4& ParentTransform);
	bool InitFromScene(const aiScene* pScene, const string& Filename);
	void InitMesh(uint MeshIndex,
		const aiMesh* paiMesh,
		vector<vec3>& Positions,
		vector<vec3>& Normals,
		vector<vec2>& TexCoords,
		vector<VertexBoneData>& Bones,
		vector<unsigned int>& Indices);
	void LoadBones(uint MeshIndex, const aiMesh* paiMesh, vector<VertexBoneData>& Bones);
	bool InitMaterials(const aiScene* pScene, const string& Filename);
	void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

	enum VB_TYPES {
		INDEX_BUFFER,
		POS_VB,
		NORMAL_VB,
		TEXCOORD_VB,
		BONE_VB,
		NUM_VBs
	};

	GLuint m_VAO;
	GLuint m_Buffers[NUM_VBs];

	struct MeshEntry {
		MeshEntry()
		{
			NumIndices = 0;
			BaseVertex = 0;
			BaseIndex = 0;
			MaterialIndex = INVALID_MATERIAL;
		}

		unsigned int NumIndices;
		unsigned int BaseVertex;
		unsigned int BaseIndex;
		unsigned int MaterialIndex;
	};

	vector<MeshEntry> m_Entries;
	//vector<Texture*> m_Textures;

	map<string, uint> m_BoneMapping; // maps a bone name to its index
	uint m_NumBones;
	vector<BoneInfo> m_BoneInfo;
	mat4 m_GlobalInverseTransform;

	const aiScene* m_pScene;
	Assimp::Importer m_Importer;
};


#endif	/* OGLDEV_SKINNED_MESH_H */

