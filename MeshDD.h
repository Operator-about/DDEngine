#ifndef MESH_CLASS
#define MESH_CLASS

#include<iostream>
#include<string>
#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
using namespace std;

class MeshClass 
{
public:
	vector <Vertex> _Vert;
	vector <GLuint> _Index;
	

	VAO _VAO;
	MeshClass(vector <Vertex>& _Vert, vector <GLuint> _Index);

	void DrawObject(MainShaderSystem& _Shader, CameraSystem& _Camera);

};



#endif
