#include <iostream>
#include <glad.h>;
#include <glfw3.h>;
#include <khrplatform.h>
#include"ShaderSystemDDEngine.h"
#include"EBO.h"
#include"VAO.h"
#include"VBO.h"
#include <thread>



using namespace std;







GLfloat _Vert[] =
{
	//Координаты										Цвет
	-0.5f,-0.5f * float(sqrt(3)) / 3		,0.0f,			0.8f,0.3f,0.02f,
	0.5f,-0.5f * float(sqrt(3)) / 3,		 0.0f,			0.8f,0.3f,0.02f,
	0.0f,0.5f * float(sqrt(3)) * 2 / 3,   0.0f,			1.0f,0.6f,0.32f,
	-0.5f / 2,0.5f * float(sqrt(3)) / 6,	 0.0f,			0.9f,0.45f,0.17f,
	0.5f / 2,0.5f * float(sqrt(3)) / 6,	 0.0f,			0.9f,0.45f,0.17f,
	0.0f,0.5f * float(sqrt(3)) / 3,		 0.0f,			0.8f,0.3f,0.02f
};

GLuint _Index[] =
{
	0,3,5,
	3,2,4,
	5,4,1
};






class DDShell 
{

public:

	
	

	void UpdateFrame(GLFWwindow* _Window)
	{
		glfwSwapBuffers(_Window);
	}
	void CloseWindow(GLFWwindow* _Window)
	{
		glfwDestroyWindow(_Window);
		glfwTerminate();
	}
	tuple<VBO, VAO, EBO> LinkVBOVAOEBOAttribute(VBO _VBOLocal, VAO _VAOLocal, EBO _EBOLocal,GLfloat _Vert[], GLuint _Index[])
	{
		gladLoadGL();
		VBO _VBO(_Vert, sizeof(_Vert));
		EBO _EBO(_Index, sizeof(_Index));
		VAO _VAO;

		_VBOLocal = _VBO;
		_EBOLocal = _EBO;
		_VAOLocal = _VAO;

		_VAOLocal.Bind();
		


		_VAOLocal.LinkAttrib(_VBOLocal, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		_VAOLocal.LinkAttrib(_VBOLocal, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * (sizeof(float))));
		_VBOLocal.UnBind();
		_VAOLocal.UnBind();
		_EBOLocal.UnBind();
		cout << "Link status: done and good" << endl;
		tuple<VBO, VAO, EBO> _All = {_VBOLocal,_VAOLocal,_EBOLocal};
		return _All;
	}
	tuple<VBO,VAO,EBO,MainShaderSystem> ActivAndBindSystem(VBO _VBO, VAO _VAO, EBO _EBO, MainShaderSystem _Shader, bool _VBOStatus, bool _VAOStatus, bool _EBOStatus, bool _ShaderStatus)
	{
		gladLoadGL();
		if (_VBOStatus == true)
		{
			_VBO.Bind();
			cout << "Bind: VBO status: done and good" << endl;
		}
		if (_VAOStatus == true)
		{
			_VAO.Bind();
			cout << "Bind: VAO status: done and good" << endl;
		}
		if (_EBOStatus == true)
		{
			_EBO.Bind();
			cout << "Bind: EBO status: done and good" << endl;
		}
		if (_ShaderStatus == true)
		{
			_Shader.Online();
			cout << "Bind: Shader status: done and good" << endl;
		}
		tuple<VBO, VAO, EBO, MainShaderSystem> _All = { _VBO,_VAO,_EBO,_Shader };
		return _All;
	}
	void ShutdownSystemComponent(VBO _VBO, VAO _VAO, EBO _EBO, MainShaderSystem _Shader, bool _VBOStatus, bool _VAOStatus, bool _EBOStatus, bool _ShaderStatus)
	{
		gladLoadGL();
		if (_VBOStatus == true)
		{
			_VBO.Offline();
			cout << "Deactivet: VBO status: done and good" << endl;
		}
		if (_VAOStatus == true)
		{
			_VAO.Offline();
			cout << "Deactivet: VAO status: done and good" << endl;
		}
		if (_EBOStatus == true)
		{
			_EBO.Offline();
			cout << "Deactivet: EBO status: done and good" << endl;
		}
		if (_ShaderStatus == true)
		{
			_Shader.Offline();
			cout << "Deactivet: Shader status: done and good" << endl;
		}
	}

	void ClearWindow(float R, float G, float B, float A)
	{
		gladLoadGL();
		glClearColor(R, G, B, A);
		glClear(GL_COLOR_BUFFER_BIT);
	}
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
	
	_ComponentEngine.LinkVBOVAOEBOAttribute(_VBO,_VAO,_EBO,_Vert,_Index);
	_ComponentEngine.ClearWindow(0.07f, 0.13f, 0.17f, 1.0f);
	_ComponentEngine.UpdateFrame(_Window);
	cout << "Startup complete, DDEngine online, welcome " << endl;

	//Обработка окна пока оно не закрыто
	while (!glfwWindowShouldClose(_Window))
	{
		_ComponentEngine.ClearWindow(0.07f, 0.13f, 0.17f, 1.0f);
		_ComponentEngine.ActivAndBindSystem(_VBO, _VAO, _EBO, _Shader, true,true,true,true);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		_ComponentEngine.UpdateFrame(_Window);
		

		glfwPollEvents();
	}

	_ComponentEngine.ShutdownSystemComponent(_VBO, _VAO, _EBO, _Shader,true,true,true,true);


	glfwDestroyWindow(_Window);
	glfwTerminate();
	return 0;
}



