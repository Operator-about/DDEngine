#include<iostream>
#include<glfw3.h>
#include<glad.h>
#include<string>
#include<thread>
#include"VBO.h"
#include"EBO.h"
#include"VAO.h"
#include"ShaderSystemDDEngine.h"
using namespace std;

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
	void LinkVBOVAOEBOAttribute(VBO _VBOLocal, VAO _VAOLocal, EBO _EBOLocal, GLfloat _Vert[], GLuint _Index[])
	{
		gladLoadGL();

		_VAOLocal.LinkAttrib(_VBOLocal, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		_VAOLocal.LinkAttrib(_VBOLocal, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
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



	}
	tuple<VBO, VAO, EBO, MainShaderSystem> ActivAndBindSystem(VBO _VBO, VAO _VAO, EBO _EBO, MainShaderSystem _Shader, bool _VBOStatus, bool _VAOStatus, bool _EBOStatus, bool _ShaderStatus, bool _OutMode)
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
