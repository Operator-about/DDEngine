#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad.h>
#include"VBO.h"

class VAO 
{
public:
	GLuint _ID;
	VAO();

	void LinkVBOSystem(VBO _VBO, GLuint _Layout);
	void Bind();
	void UnBind();
	void Offline();
};

#endif
