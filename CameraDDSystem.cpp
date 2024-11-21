#include "Camera.h"

CameraSystem::CameraSystem(int _Width, int _Hegth, vec3 _Position) 
{
	CameraSystem::_HegthCamera = _Hegth;
	CameraSystem::_WidthCamera = _Width;
	_PositionCamera = _Position;
}

void CameraSystem::UpdateMatrixCamera(float _FOV, float _NearPlane, float _FarPlane)
{
	mat4 _View = mat4(1.0f);
	mat4 _Proj = mat4(1.0f);

	_View = lookAt(_PositionCamera,_PositionCamera+_Orient, _Up);
	_Proj = perspective(radians(_FOV), (float)(_WidthCamera / _HegthCamera), _NearPlane, _FarPlane);

	_CameraMatrix = _Proj * _View;
}

void CameraSystem::CameraMatrix(MainShaderSystem& _Shader, const char* _UniformVar) 
{
	glUniformMatrix4fv(glGetUniformLocation(_Shader._ID, _UniformVar), 1, GL_FALSE, value_ptr(_CameraMatrix));
}




void CameraSystem::Input(GLFWwindow* _Window) 
{
	if (glfwGetKey(_Window,GLFW_KEY_W) == GLFW_PRESS) 
	{
		_PositionCamera += _Speed * _Orient;
		cout << "Press key: W" << endl;
	}
	if (glfwGetKey(_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_PositionCamera += _Speed * -_Orient;
		cout << "Press key: S" << endl;
	}
	if (glfwGetKey(_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_PositionCamera += _Speed * -normalize(cross(_Orient, _Up));
		cout << "Press key: A" << endl;
	}
	if (glfwGetKey(_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_PositionCamera += _Speed * normalize(cross(_Orient, _Up));
		cout << "Press key: D" << endl;
	}
	if (glfwGetKey(_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		_PositionCamera += _Speed * _Up;
		cout << "Press key: Space" << endl;
	}
	if (glfwGetKey(_Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		_PositionCamera += _Speed * -_Up;
		cout << "Press key: LeftCTRL" << endl;
	}
	if (glfwGetKey(_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		_Speed = 20.0f;
		cout << "Press key: +LeftSHIFT" << endl;
	}
	else if (glfwGetKey(_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		_Speed = 10.0f;
		cout << "Press key: -LeftShift" << endl;
	}

	if (glfwGetMouseButton(_Window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 
	{
		glfwSetInputMode(_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (_Click) 
		{
			glfwSetCursorPos(_Window, (_WidthCamera / 2), (_HegthCamera / 2));
			_Click = false;
		}


		double _MouseX;
		double _MouseY;
		glfwGetCursorPos(_Window, &_MouseX,&_MouseY);

		float _RotationX = _Sent * (float)(_MouseY-(_HegthCamera/2))/_HegthCamera;
		float _RotationY = _Sent * (float)(_MouseX -(_HegthCamera / 2)) / _HegthCamera;

		vec3 _OrintNew = rotate(_Orient,radians(-_RotationX), normalize(cross(_Orient, _Up)));
		if (!(angle(_OrintNew,_Up) <= radians(5.0f) or angle(_OrintNew, -_Up) <= radians(5.0f)))
		{
			_Orient = _OrintNew;
		}

		_Orient = rotate(_Orient, radians(-_RotationY), _Up);

		glfwSetCursorPos(_Window, (_WidthCamera/2),(_HegthCamera/2));

	}
	if (glfwGetMouseButton(_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		_Click = true;
	}
}