#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad.h>

class EBO
{
public:
	GLuint _ID;
	EBO(GLfloat* _Vert, GLsizeiptr _Size);

	void Bind();
	void UnBind();
	void Offline();
	void Offline();
};


#endif
