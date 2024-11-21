#include<iostream>
#include<glad.h>
#include<glfw3.h>
#include<khrplatform.h>
#include"MeshDD.h"
#include"IFEShell.h"

using namespace std;
using namespace glm;

const unsigned int _Width = 800;
const unsigned int _Hegth = 800;

Vertex _Vert[] =
{
	Vertex{vec3(-1.0f,0.0f,1.0f), vec3(0.0f,1.0f,0.0f),vec3(1.0f,1.0f,1.0f)},
	Vertex{vec3(-1.0f,0.0f,-1.0f), vec3(0.0f,1.0f,0.0f),vec3(1.0f,1.0f,1.0f)},
	Vertex{vec3(1.0f,0.0f,-1.0f), vec3(0.0f,1.0f,0.0f),vec3(1.0f,1.0f,1.0f)},
	Vertex{vec3(1.0f,0.0f,1.0f), vec3(0.0f,1.0f,0.0f),vec3(1.0f,1.0f,1.0f)}
};

GLuint _Index[] =
{
	0,1,2,
	0,2,3,
	4,6,5,
	7,9,8,
	10,12,11,
	13,15,14
};


Vertex _LightCoordinate[] = 
{
	Vertex{vec3(-0.1f,-0.1f,0.1f)},
	Vertex{vec3(-0.1f,-0.1f,0.1f)},
	Vertex{vec3(0.1f,-0.1f,-0.1f)},
	Vertex{vec3(0.1f,-0.1f,0.1f)},
	Vertex{vec3(-0.1f,0.1f,0.1f)},
	Vertex{vec3(-0.1f,0.1f,-0.1f)},
	Vertex{vec3(0.1f,0.1f,-0.1f)},
	Vertex{vec3(0.1f,0.1f,0.1f)}
};

GLuint _LightIndex[] =
{
	0,1,2,
	0,2,3,
	0,4,7,
	0,7,3,
	3,7,6,
	3,6,2,
	2,6,5,
	2,5,1,
	1,5,4,
	1,4,0,
	4,5,6,
	4,6,7
};


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
	vector<Vertex> _VertV(_Vert,_Vert+sizeof(_Vert)/sizeof(Vertex));
	vector<GLuint> _Ind(_Index, _Index + sizeof(_Index) / sizeof(GLuint));
	MeshClass _Floor(_VertV, _Ind);




	
	IFEShell _ComponentEngine;

	//Свет. ПОКА НЕ ТРОГАТЬ!
	MainShaderSystem _LightShader("LightVert.vert", "FragLight.frag");
	vector<Vertex> _LightVert(_LightCoordinate, _LightCoordinate + sizeof(_LightCoordinate) / sizeof(Vertex));
	vector<GLuint> _IndexLightEBO(_LightIndex, _LightIndex + sizeof(_LightIndex) / sizeof(GLuint));
	MeshClass _Light(_LightVert, _IndexLightEBO);
	_ComponentEngine.BindLightSystem(_Shader,_LightShader);

	
	
	
	
	_ComponentEngine.ClearWindow(0.07f, 0.13f, 0.17f, 1.0f);
	_ComponentEngine.UpdateFrame(_Window);
	cout << "Startup complete, DDEngine online, welcome " << endl;

	glEnable(GL_DEPTH_TEST);
	CameraSystem _MainCamera(_Width, _Hegth, vec3(0.0f, 0.0f, 2.0f));
	cout << "Camera add: Done!" << endl;

	//Обработка окна пока оно не закрыто
	while (!glfwWindowShouldClose(_Window))
	{
		_ComponentEngine.ClearWindow(0.07f, 0.13f, 0.17f, 1.0f);
		

		_MainCamera.Input(_Window);
		_MainCamera.UpdateMatrixCamera(45.0f,0.1f,100.0f);
		
		_Floor.DrawObject(_Shader, _MainCamera);
		_Light.DrawObject(_LightShader, _MainCamera);

		_ComponentEngine.UpdateFrame(_Window);


		glfwPollEvents();
	}

	_ComponentEngine.ShutdownSystemComponent(_Shader);
	_ComponentEngine.ShutdownSystemComponent(_LightShader);

	glfwDestroyWindow(_Window);
	glfwTerminate();
	return 0;
}




