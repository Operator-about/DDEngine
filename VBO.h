#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad.h>

class VBO 
{
public:
	GLuint _ID;
	VBO(GLfloat*_Vert,GLsizeiptr _Size);

	void Bind();
	void UnBind();
	void Offline();
};


#endif
