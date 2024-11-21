#include"VBO.h"
#include<vector>
using namespace std;

VBO::VBO(vector<Vertex>& _Vert)
{
	glGenBuffers(1,&_ID);
	glBindBuffer(GL_ARRAY_BUFFER, _ID);
	glBufferData(GL_ARRAY_BUFFER, _Vert.size() * sizeof(Vertex), _Vert.data(), GL_STATIC_DRAW);
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