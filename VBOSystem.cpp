#include"VBO.h"

VBO::VBO(GLfloat* _Vert, GLsizeiptr _Size)
{
	glGenBuffers(1,&_ID);
	glBindBuffer(GL_ARRAY_BUFFER, _ID);
	glBufferData(GL_ARRAY_BUFFER, _Size, _Vert, GL_STATIC_DRAW);
}

void VBO::Bind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, _ID);
}

void VBO::UnBind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::Offline() 
{
	glDeleteBuffers(1,&_ID);
}