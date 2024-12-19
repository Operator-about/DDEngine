#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;
//layout (location=2) in vec2 aTexCoords;



out vec3 CurrentPos;
out vec3 Normal;
//out vec2 TexCoords;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;


void main()
{
	CurrentPos = vec3(model*translation*-rotate*scale*vec4(aPos,1.0f));
	
	Normal = aNormal;
	
	//TexCoords = aTexCoords;

	gl_Position=camMatrix*vec4(CurrentPos,1.0);
	

	
}