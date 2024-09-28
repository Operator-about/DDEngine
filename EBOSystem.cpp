#include"EBO.h"

EBO::EBO(GLfloat* _Indices, GLsizeiptr _Size)
{
	glGenBuffers(1, &_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _Size, _Indices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
}

void EBO::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void EBO::Offline()
{
	glDeleteBuffers(1, &_ID);
}