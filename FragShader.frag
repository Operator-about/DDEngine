#version 330 core
out vec4 FragColor;

in vec3 �olor;

void main()
{
	FragColor = vec4(�olor,1.0f);
}