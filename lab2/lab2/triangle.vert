#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;

out vec3 col;
out vec3 pos;

uniform float move_x;
uniform float move_y;

void main()
{
	gl_Position = vec4(aPos.x+move_x, aPos.y+move_y, aPos.z, 1.f);
	col = aCol;
	//pos = vec3(aPos)
	pos = vec3(aPos.x+move_x, aPos.y+move_y, aPos.z);
}
