#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad.h>
#include<vector>
using namespace std;

class EBO
{
public:
	GLuint _ID;
	EBO(vector<GLuint>& _Index);

	void Bind();
	void UnBind();
	void Offline();
};


#endif
