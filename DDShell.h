#include<iostream>
#include<glfw3.h>
#include<glad.h>
#include<string>
#include<thread>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include"VBO.h"
#include"EBO.h"
#include"VAO.h"
#include"ShaderSystemDDEngine.h"


using namespace std;
using namespace glm;

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
	
	void BindLightSystem(MainShaderSystem _Shader, MainShaderSystem _LightShader) 
	{
		gladLoadGL();
		
		


		vec4 _LightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);


		vec3 _LightPos = vec3(0.5f, 0.5f, 0.5f);
		mat4 _LightModel = mat4(1.0f);
		_LightModel = translate(_LightModel, _LightPos);

		vec3 _PyramidPos = vec3(0.0f, 0.0f, 0.0f);
		mat4 _PyramidModel = mat4(1.0f);
		_PyramidModel = translate(_PyramidModel, _PyramidPos);

		_LightShader.Online();
		glUniformMatrix4fv(glGetUniformLocation(_LightShader._ID, "model"), 1, GL_FALSE, value_ptr(_LightModel));
		glUniform4f(glGetUniformLocation(_LightShader._ID, "LightColor"), _LightColor.x, _LightColor.y, _LightColor.z, _LightColor.w);
		_Shader.Online();
		glUniformMatrix4fv(glGetUniformLocation(_Shader._ID, "model"), 1, GL_FALSE, value_ptr(_PyramidModel));
		glUniform4f(glGetUniformLocation(_Shader._ID, "LightColor"), _LightColor.x, _LightColor.y, _LightColor.z, _LightColor.w);
		glUniform3f(glGetUniformLocation(_Shader._ID, "LightPos"), _LightColor.x, _LightColor.y, _LightColor.z);
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
	void ShutdownSystemComponent(MainShaderSystem _Shader)
	{
		gladLoadGL();
		
	
		_Shader.Offline();
		_DebugInfoText = "Deactivet: Shader status: done and good";
		DebugTextOutput();

	
		_DebugInfoText = "Status Bind: offline!";
	}

	void ClearWindow(float R, float G, float B, float A)
	{
		gladLoadGL();
		glClearColor(R, G, B, A);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void DebugTextOutput()
	{
		cout << _DebugInfoText << endl;
	}
};
