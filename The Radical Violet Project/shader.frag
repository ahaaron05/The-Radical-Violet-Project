#version 330 core

in vec3 someColor;
in vec3 somePos;
out vec4 FragColor;

void main()
{
	FragColor = vec4(someColor, 1);
}