#include"VAO.h"

VAO::VAO() 
{
	glGenVertexArrays(1, &_ID);
}

void VAO::LinkVBOSystem(VBO _VBO, GLuint _Layout) 
{
	_VBO.Bind();

	glVertexAttribPointer(_Layout,3,GL_FLOAT,GL_FALSE,0,(void*)0);
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