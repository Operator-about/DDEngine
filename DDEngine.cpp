#include <iostream>
#include <glad.h>;
#include <glfw3.h>;
#include <khrplatform.h>
using namespace std;

#include"ShaderSystemDDEngine.h"
#include"EBO.h"
#include"VAO.h"
#include"VBO.h"




GLfloat _Vert[] =
{
	-0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,
	0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,
	0.0f,0.5f * float(sqrt(3)) * 2 / 3,0.0f,
	-0.5f / 2,0.5f * float(sqrt(3)) / 6,0.0f,
	0.5f / 2,0.5f * float(sqrt(3)) / 6,0.0f,
	0.0f,0.5f * float(sqrt(3)) / 3,0.0f,
};

GLfloat _Index[] =
{
	0,3,5,
	3,2,4,
	5,4,1
};





int main(){



	//Инцилизация OpenGL
	glfwInit();

	//Подсказки для OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	

	//Создание окна
	//GLFWindow - класс окна openGL, функция: glfwCreateWindow - создаёт окно
	GLFWwindow* _Window = glfwCreateWindow(800,600, "DDEngine", NULL, NULL);
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
	
	MainShaderSystem _ShadderSystem("VertShader.vert","FragShader.frag");
	
	if (glad_glGetError != NULL) 
	{
		cout << "Error detected!" << endl;
	}

	VAO _VAO;
	_VAO.Bind();

	VBO _VBO(_Vert, sizeof(_Vert));
	EBO _EBO(_Index, sizeof(_Index));

	
	_VAO.LinkVBOSystem(_VBO,0);
	_VAO.UnBind();
	_VBO.UnBind();
	_EBO.UnBind();

	




	glClearColor(0.07f,0.13f,0.17f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(_Window);

	//Обработка окна пока оно не закрыто
	while (!glfwWindowShouldClose(_Window)) 
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		_ShadderSystem.Online();
		_VAO.Bind();
		glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
		glfwSwapBuffers(_Window);

		glfwPollEvents();
	}

	_VAO.Offline();
	_VBO.Offline();
	_EBO.Offline();
	_ShadderSystem.Offline();


	glfwDestroyWindow(_Window);
	glfwTerminate();
	return 0;
}

