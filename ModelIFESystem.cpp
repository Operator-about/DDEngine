#include<iostream>
#include<string>
#include<glad.h>
#include<glfw3.h>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"Mesh.h"
#include"ShaderSystemIFE.h"
#include"Model.h"
#include"Camera.h"

using namespace std;
using namespace Assimp;
using namespace glm;


void ModelSystem::Draw(MainShaderSystem& _Shader,CameraSystem& _Camera ) 
{
	for (unsigned int i = 0; i < _Mesh.size(); i++)
	{
		_Mesh[i].DrawMesh(_Shader, _Camera);
	}
		
}

int ModelSystem::Load(string _File) 
{
	Importer _Import;
	const aiScene* _Scene = _Import.ReadFile(_File, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!_Scene||_Scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE||!_Scene->mRootNode) 
	{
		cout << "Error Assimp:" << _Import.GetErrorString() << endl;
		return -1;
	}

	_Direct = _File.substr(0, _File.find_last_of('/'));
	Node(_Scene->mRootNode, _Scene);
}

void ModelSystem::Node(aiNode* _Node, const aiScene* _Scene) 
{
	for (unsigned int i = 0; i < _Node->mNumMeshes; i++) 
	{
		cout << _Node << endl;
		aiMesh* _MeshF = _Scene->mMeshes[_Node->mMeshes[i]];
		_Mesh.push_back(Mesh(_MeshF, _Scene));
	}
	for (unsigned int i = 0; i < _Node->mNumChildren; i++)
	{
		Node(_Node->mChildren[i], _Scene);
	}
}



MeshSystemF ModelSystem::Mesh(aiMesh* _Mesh, const aiScene* _Scene) 
{
	cout << "Load model other system... please wait" << endl;
	vector<VertexF> _Vert;
	vector<unsigned int> _Index;
	

	for (unsigned int i = 0; i < _Mesh->mNumVertices; i++)
	{
		vec3 _Vector;
		VertexF _Vertex;
		

		_Vector.x = _Mesh->mVertices[i].x;
		_Vector.y = _Mesh->mVertices[i].y;
		_Vector.z = _Mesh->mVertices[i].z;
		

		_Vertex._Position = _Vector;

		cout << "Position lock" << endl;
		cout << "Loading normals model" << endl;
		if (_Mesh->HasNormals())
		{
			_Vector.x = _Mesh->mNormals[i].x;
			_Vector.y = _Mesh->mNormals[i].y;
			_Vector.z = _Mesh->mNormals[i].z;
			
			_Vertex._Normal = _Vector;
			cout << "Loading normals model: done!" << endl;
		}
		cout << "Loading texture coordinate model" << endl;
		if (_Mesh->mTextureCoords[0])
		{
			vec2 _Vec;
			_Vec.x = _Mesh->mTextureCoords[0][i].x;
			_Vec.y = _Mesh->mTextureCoords[0][i].y;
			_Vertex._TexCoord = _Vec;
			cout << "Loading texture coordinate model: done!" << endl;
		}
		else
		{
			_Vertex._TexCoord = vec2(0.0f,0.0f);
		}

		_Vert.push_back(_Vertex);
		

	}
	cout << "Count Vertical model:" << _Mesh->mNumVertices << endl;
	cout << "Load model index... please wait" << endl;
	for (unsigned int i = 0; i < _Mesh->mNumFaces; i++)
	{
		aiFace _Face = _Mesh->mFaces[i];
		for (unsigned int j = 0; j < _Face.mNumIndices; j++)
			_Index.push_back(_Face.mIndices[j]);
	}
	cout << "Count Index model:" << _Mesh->mNumFaces << endl;


	return MeshSystemF(_Vert, _Index);
}
