#ifndef SHADER_SYSTEM_H
#define SHADER_SYSTEM_H

#include<glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
using namespace std;

string GetFile(const char* _FileName);


class MainShaderSystem 
{
public:
	GLuint _ID;
	MainShaderSystem(const char* _VertFile, const char* _FragFile);

	void Int(const string& _Name, bool _Value) const;
	void Online();
	void Offline();



	
};

#endif
