#version 330 core
out vec4 FragColor;

in vec3 ñolor;

void main()
{
	FragColor = vec4(ñolor,1.0f);
}