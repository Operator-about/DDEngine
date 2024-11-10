#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad.h>
#include"VBO.h"

class VAO 
{
public:
	GLuint _ID;
	VAO();

	void LinkAttrib(VBO _VBO, GLuint _Layout, GLuint _NumComponent, GLenum _Type, GLsizeiptr _Stride, void* _Offest);
	void Bind();
	void UnBind();
	void Offline();
};

#endif
