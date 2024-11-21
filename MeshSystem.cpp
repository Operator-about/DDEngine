#include"MeshDD.h"
using namespace std;


MeshClass::MeshClass(vector <Vertex>& _VertF, vector <GLuint> _IndexF) 
{

	MeshClass::_Vert = _VertF;
	MeshClass::_Index = _IndexF;

	_VAO.Bind();
	VBO _VBO(_VertF);
	EBO _EBO(_IndexF);


	_VAO.LinkAttrib(_VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	_VAO.LinkAttrib(_VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	_VAO.LinkAttrib(_VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	_VAO.LinkAttrib(_VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));




	_VBO.UnBind();
	_VAO.UnBind();
	_EBO.UnBind();


}
void MeshClass::DrawObject(MainShaderSystem& _Shader, CameraSystem& _Camera) 
{
	_Shader.Online();
	_VAO.Bind();

	glUniform3f(glGetUniformLocation(_Shader._ID, "camPos"), _Camera._PositionCamera.x, _Camera._PositionCamera.y, _Camera._PositionCamera.z);
	_Camera.CameraMatrix(_Shader,"camMatrix");

	glDrawElements(GL_TRIANGLES,_Index.size(),GL_UNSIGNED_INT,0);

}