#include<iostream>
#include<glfw3.h>
#include<glad.h>
#include<string>
#include<thread>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"ShaderSystemIFE.h"


using namespace std;
using namespace glm;

class IFEShell
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
	
	void BindLightSystem(MainShaderSystem _Shader) 
	{
		gladLoadGL();
		
		


		vec4 _LightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		vec3 _LightPos = vec3(0.5f, 0.5f, 0.5f);
		mat4 _LightModel = mat4(1.0f);
		_LightModel = translate(_LightModel, _LightPos);

		_Shader.Online();
		glUniform4f(glGetUniformLocation(_Shader._ID, "LightColor"), _LightColor.x, _LightColor.y, _LightColor.z, _LightColor.w);
		glUniform3f(glGetUniformLocation(_Shader._ID, "LightPos"), _LightColor.x, _LightColor.y, _LightColor.z);
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
