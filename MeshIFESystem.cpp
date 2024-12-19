#include<iostream>
#include<glad.h>
#include<glfw3.h>
#include<khrplatform.h>
#include"IFEShell.h"
#include"Camera.h"
#include"Mesh.h"

using namespace std;
using namespace glm;

MeshSystemF::MeshSystemF(vector<VertexF> _VertF, vector<GLuint> _IndexF) 
{
	this->_Vert = _VertF;
	this->_Index = _IndexF;

	ActivationMesh();
}

void MeshSystemF::ActivationMesh() 
{
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	glBufferData(GL_ARRAY_BUFFER, _Vert.size() * sizeof(VertexF), &_Vert[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _Index.size() * sizeof(unsigned int), &_Index[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexF), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexF), (void*)offsetof(VertexF, _Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexF), (void*)offsetof(VertexF, _TexCoord));

	glBindVertexArray(0);
}

void MeshSystemF::DrawMesh(MainShaderSystem& _Shader, CameraSystem& _Camera) 
{
	_Shader.Online();
	glBindVertexArray(_VAO);

	glUniform3f(glGetUniformLocation(_Shader._ID, "camPos"), _Camera._PositionCamera.x, _Camera._PositionCamera.y, _Camera._PositionCamera.x);
	_Camera.CameraMatrix(_Shader, "camMatrix");


	glDrawElements(GL_TRIANGLES, _Index.size(),GL_UNSIGNED_INT,0);
	//glBindVertexArray(0);
}