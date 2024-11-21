#version 330 core
out vec4 FragColor;

in vec3 CurrentPos;
in vec3 Normal;
in vec3 color;



uniform vec4 LightColor;
uniform vec3 LightPos;

void main()
{
	vec3 normal = normalize(Normal);
	vec3 LightDirections = normalize(LightPos - CurrentPos);

	float diffuse = max(dot(normal,LightDirections),0.0f);

	FragColor = vec4(color,1.0f) * LightColor * diffuse;
}