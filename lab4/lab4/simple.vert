#version 330 core
uniform mat4 transformation;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;

out vec3 col;

void main()
{
	gl_Position = transformation * vec4(aPos, 1.f);
	col = aCol;
}
