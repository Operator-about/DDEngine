#ifndef CLASS_CAMERA
#define CLASS_CAMERA

#include<glad.h>
#include<glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"ShaderSystemIFE.h"
using namespace glm;



class CameraSystem 
{
public:
	vec3 _PositionCamera;
	vec3 _Orient = vec3(0.0f,0.0f,-1.0f);
	vec3 _Up = vec3(0.0f,1.0f,0.0f);
	mat4 _CameraMatrix = mat4(1.0f);

	bool _Click = true;

	int _WidthCamera;
	int _HegthCamera;

	float _Speed = 10.1f;
	float _Sent = 100.0f;

	CameraSystem(int _Width, int _Hegth, vec3 _Position);

	void UpdateMatrixCamera(float _FOV, float _NearPlane, float _FarPlane);
	void CameraMatrix(MainShaderSystem& _Shader, const char* _UniformVar);
	void Input(GLFWwindow* _Window);
};


#endif
