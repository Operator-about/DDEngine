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
	//Координаты										
	-0.5f,-0.5f * float(sqrt(3)) / 3		,0.0f,			
	0.5f,-0.5f * float(sqrt(3)) / 3,		 0.0f,			
	0.0f,0.5f * float(sqrt(3)) * 2 / 3,      0.0f,			
	-0.5f / 2,0.5f * float(sqrt(3)) / 6,	 0.0f,			
	0.5f / 2,0.5f * float(sqrt(3)) / 6,	     0.0f,			
	0.0f,0.5f * float(sqrt(3)) / 3,		     0.0f,			
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

	
	string _DebugInfoText;

	void UpdateFrame(GLFWwindow* _Window)
	{
		glfwSwapBuffers(_Window);
	}
	void CloseWindow(GLFWwindow* _Window)
	{
		glfwDestroyWindow(_Window);
		glfwTerminate();
	}
	void LinkVBOVAOEBOAttribute(VBO _VBOLocal, VAO _VAOLocal, EBO _EBOLocal,GLfloat _Vert[], GLuint _Index[])
	{
		gladLoadGL();

		_VAOLocal.LinkAttrib(_VBOLocal, 0);
		_VBOLocal.UnBind();
		_DebugInfoText = "Status VBO: UnBind!";
		DebugTextOutput();
		_VAOLocal.UnBind();
		_DebugInfoText = "Status VAO: UnBind!";
		DebugTextOutput();
		_EBOLocal.UnBind();
		_DebugInfoText = "Status EBO: UnBind!";
		DebugTextOutput();

		_DebugInfoText = "Status Link: online!";
		DebugTextOutput();


		_DebugInfoText = "Return variable... pls wait";
		DebugTextOutput();
		
	}
	tuple<VBO,VAO,EBO,MainShaderSystem> ActivAndBindSystem(VBO _VBO, VAO _VAO, EBO _EBO, MainShaderSystem _Shader, bool _VBOStatus, bool _VAOStatus, bool _EBOStatus, bool _ShaderStatus, bool _OutMode)
	{
		gladLoadGL();
		if (_VBOStatus == true)
		{
			_VBO.Bind();
			_DebugInfoText = "Bind: VBO status: done and good";
			if (_OutMode == true)
			{
				DebugTextOutput();
			}
		}
		if (_VAOStatus == true)
		{
			_VAO.Bind();
			_DebugInfoText = "Bind: VAO status: done and good";
			if (_OutMode == true)
			{
				DebugTextOutput();
			}
		}
		if (_EBOStatus == true)
		{
			_EBO.Bind();
			_DebugInfoText = "Bind: EBO status: done and good";
			if (_OutMode == true)
			{
				DebugTextOutput();
			}
		}
		if (_ShaderStatus == true)
		{
			_Shader.Online();
			_DebugInfoText = "Bind: Shader status: done and good";
			if (_OutMode == true)
			{
				DebugTextOutput();
			}
		}
		_DebugInfoText = "Status Bind: online!";

		tuple<VBO, VAO, EBO, MainShaderSystem> _All = { _VBO,_VAO,_EBO,_Shader };
		if (_OutMode == true)
		{
			_DebugInfoText = "Return variable... pls wait";
			DebugTextOutput();
		}
		
		
		return _All;
	}
	void ShutdownSystemComponent(VBO _VBO, VAO _VAO, EBO _EBO, MainShaderSystem _Shader, bool _VBOStatus, bool _VAOStatus, bool _EBOStatus, bool _ShaderStatus)
	{
		gladLoadGL();
		if (_VBOStatus == true)
		{
			_VBO.Offline();
			_DebugInfoText = "Deactivet: VBO status: done and good";
			DebugTextOutput();
		}
		if (_VAOStatus == true)
		{
			_VAO.Offline();
			_DebugInfoText = "Deactivet: VAO status: done and good";
			DebugTextOutput();
		}
		if (_EBOStatus == true)
		{
			_EBO.Offline();
			_DebugInfoText = "Deactivet: EBO status: done and good";
			DebugTextOutput();
			
		}
		if (_ShaderStatus == true)
		{
			_Shader.Offline();
			_DebugInfoText = "Deactivet: Shader status: done and good";
			DebugTextOutput();
			
		}
		_DebugInfoText = "Status Bind: offline!";
	}

	void ClearWindow(float R, float G, float B, float A)
	{
		gladLoadGL();
		glClearColor(R, G, B, A);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void DebugTextOutput() 
	{
		cout << _DebugInfoText << endl;
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
		_ComponentEngine.ActivAndBindSystem(_VBO, _VAO, _EBO, _Shader, false,true,false,true,false);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		_ComponentEngine.UpdateFrame(_Window);
		

		glfwPollEvents();
	}

	_ComponentEngine.ShutdownSystemComponent(_VBO, _VAO, _EBO, _Shader,true,true,true,true);


	glfwDestroyWindow(_Window);
	glfwTerminate();
	return 0;
}



