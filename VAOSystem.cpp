#include"VAO.h"

VAO::VAO() 
{
	glGenVertexArrays(1, &_ID);
}

void VAO::LinkAttrib(VBO _VBO, GLuint _Layout, GLuint _NumComponent, GLenum _Type, GLsizeiptr _Stride, void* _Offest)
{
	_VBO.Bind();

	glVertexAttribPointer(_Layout,_NumComponent,_Type,GL_FALSE,_Stride,_Offest);
	glEnableVertexAttribArray(_Layout);

	_VBO.UnBind();
}

void VAO::Bind() 
{
	glBindVertexArray(_ID);
}

void VAO::UnBind() 
{
	glBindVertexArray(0);
}

void VAO::Offline() 
{
	glDeleteVertexArrays(1,&_ID);
}