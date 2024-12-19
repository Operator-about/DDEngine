#ifndef MODEL_CLASS
#define MODEL_CLASS

#include<iostream>
#include<string>
#include<glad.h>
#include<glfw3.h>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include"Mesh.h"
#include"ShaderSystemIFE.h"
#include"Camera.h"
using namespace std;
using namespace Assimp;


class ModelSystem 
{
public:
	ModelSystem(string _File) 
	{
		Load(_File);
	}
	void Draw(MainShaderSystem& _Shader, CameraSystem& _Camera);
private:
	vector<MeshSystemF> _Mesh;
	string _Direct;

	int Load(string _File);
	void Node(aiNode* _Node, const aiScene* _Scene);
	MeshSystemF Mesh(aiMesh* _Mesh, const aiScene* _Scene);
};




#endif
