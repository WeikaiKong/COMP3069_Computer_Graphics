#version 330 core

in vec3 col;

out vec4 fragCol;

uniform vec3 uCol;

void main()
{
	fragCol = vec4(uCol, 1.f);
}
