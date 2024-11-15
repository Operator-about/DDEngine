﻿#include<iostream>
#include<glad.h>;
#include<glfw3.h>;
#include<khrplatform.h>
#include"ShaderSystemDDEngine.h"
#include"EBO.h"
#include"VAO.h"
#include"VBO.h"
#include"DDShell.h"
using namespace std;


GLfloat _Vert[] =
{
	//Координаты							        //Цвет						
	-0.5f,-0.5f * float(sqrt(3)) / 3		,0.0f,  0.8f,0.3f,  0.02f,			
	0.5f,-0.5f * float(sqrt(3)) / 3,		 0.0f,  0.8f,0.3f,  0.02f,
	0.0f,0.5f * float(sqrt(3)) * 2 / 3,      0.0f,  1.0f,0.6f,  0.32f,
	-0.5f / 2,0.5f * float(sqrt(3)) / 6,	 0.0f,  0.9f,0.45f, 0.17f,
	0.5f / 2,0.5f * float(sqrt(3)) / 6,	     0.0f,  0.9f,0.45f, 0.17f,
	0.0f,0.5f * float(sqrt(3)) / 3,		     0.0f,  0.8f,0.3f,  0.02f,
};

GLuint _Index[] =
{
	10,3,5,
	3,2,4,
	5,4,1
};


int main() 
{
	
	
	


	//Инцилизация OpenGL
	glfwInit();

	//Подсказки для OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	cout << "Startup DDEngine" << endl;
	
	

	

	//Создание окна
	//GLFWindow - класс окна openGL, функция: glfwCreateWindow - создаёт окно
	GLFWwindow* _Window = glfwCreateWindow(800, 600, "DDEngine", NULL, NULL);
	if (_Window == NULL)
	{
		cout << "Fail: create window" << endl;
		glfwTerminate();
		return -1;
	}
	//Запуск окна через: glfwMakeContextCurrent 
	glfwMakeContextCurrent(_Window);

	gladLoadGL();
	glViewport(0,0,800,800);
	MainShaderSystem _Shader("VertShader.vert", "FragShader.frag");
	DDShell _ComponentEngine;


	VAO _VAO;
	_VAO.Bind();
	VBO _VBO(_Vert, sizeof(_Vert));
	EBO _EBO(_Index,sizeof(_Index));
	GLuint _IID = glGetUniformLocation(_Shader._ID, "scale");;
	
	_ComponentEngine.LinkVBOVAOEBOAttribute(_VBO,_VAO,_EBO,_Vert,_Index);
	_ComponentEngine.ClearWindow(0.07f, 0.13f, 0.17f, 1.0f);
	_ComponentEngine.UpdateFrame(_Window);
	cout << "Startup complete, DDEngine online, welcome " << endl;

	//Обработка окна пока оно не закрыто
	while (!glfwWindowShouldClose(_Window))
	{
		_ComponentEngine.ClearWindow(0.07f, 0.13f, 0.17f, 1.0f);
		_ComponentEngine.ActivAndBindSystem(_VBO, _VAO, _EBO, _Shader, false,true,false,true,false);
		glUniform1f(_IID,0.5f);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		_ComponentEngine.UpdateFrame(_Window);
		

		glfwPollEvents();
	}

	_ComponentEngine.ShutdownSystemComponent(_VBO, _VAO, _EBO, _Shader,true,true,true,true);


	glfwDestroyWindow(_Window);
	glfwTerminate();
	return 0;
}



