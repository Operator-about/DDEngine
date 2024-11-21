#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>
#include<glad.h>
#include<vector>
using namespace glm;
using namespace std;


struct Vertex 
{
	vec3 _Pos;
	vec3 _Normal;
	vec3 _Color;
};


class VBO 
{
public:

	GLuint _ID;
	VBO(vector<Vertex>& _Vert);

	void Bind();
	void UnBind();
	void Offline();
};


#endif
