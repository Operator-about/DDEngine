#include<iostream>
#include<glad.h>
#include<glfw3.h>
#include<khrplatform.h>
#include"IFEShell.h"
#include"Camera.h"
#include"Model.h"
#include"Mesh.h"

using namespace std;
using namespace glm;

const unsigned int _Width = 800;
const unsigned int _Hegth = 800;




int main()
{





	//Инцилизация OpenGL
	glfwInit();

	//Подсказки для OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	cout << "Startup ImpulseForceEngine" << endl;



	


	//Создание окна
	//GLFWindow - класс окна openGL, функция: glfwCreateWindow - создаёт окно
	GLFWwindow* _Window = glfwCreateWindow(_Width, _Hegth, "ImpulseForceEngine", NULL, NULL);
	if (_Window == NULL)
	{
		cout << "Fail: create window" << endl;
		glfwTerminate();
		return -1;
	}

	//Запуск окна через: glfwMakeContextCurrent 
	glfwMakeContextCurrent(_Window);
	

	gladLoadGL();
	glViewport(0, 0, _Width,_Hegth);
	MainShaderSystem _Shader("VertShader.vert", "FragShader.frag");
	IFEShell _ComponentEngine;
	cout << "Load Model" << endl;
	ModelSystem _Import("Model/Cube.obj");
	//_ComponentEngine.BindLightSystem(_Shader);
	_ComponentEngine.ClearWindow(0.07f, 0.13f, 0.17f, 1.0f);
	_ComponentEngine.UpdateFrame(_Window);
	cout << "Startup complete, DDEngine online, welcome " << endl;

	glEnable(GL_DEPTH_TEST);
	cout << "Load Camera" << endl;
	CameraSystem _MainCamera(_Width, _Hegth, vec3(0.0f, 0.0f, 2.0f));
	cout << "Component load done!" << endl;



	//Обработка окна пока оно не закрыто
	while (!glfwWindowShouldClose(_Window))
	{
		_ComponentEngine.ClearWindow(0.07f, 0.13f, 0.17f, 1.0f);
		
		_Shader.Online();

		_MainCamera.Input(_Window);
		_MainCamera.UpdateMatrixCamera(45.0f,0.1f,100.0f);

		_Import.Draw(_Shader, _MainCamera);

		_ComponentEngine.UpdateFrame(_Window);


		glfwPollEvents();
	}

	_ComponentEngine.ShutdownSystemComponent(_Shader);


	glfwDestroyWindow(_Window);
	glfwTerminate();
	return 0;
}






