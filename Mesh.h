#ifndef CLASS_MESH
#define CLASS_MESH
#include<glad.h>
#include<glfw3.h>
#include<glm/glm.hpp>
#include<vector>
#include"ShaderSystemIFE.h"
#include"Camera.h"

using namespace std;
using namespace glm;

struct VertexF
{
	vec3 _Position;
	vec3 _Normal;
	vec2 _TexCoord;
};




class MeshSystemF
{
public:

	vector<VertexF> _Vert;
	vector<unsigned int> _Index;


	MeshSystemF(vector<VertexF> _VertF, vector<unsigned int> _IndexF);
	void DrawMesh(MainShaderSystem& _Shader, CameraSystem& _Camera);

private:
	
	unsigned int _VBO, _VAO, _EBO;

	void ActivationMesh();


};

#endif



