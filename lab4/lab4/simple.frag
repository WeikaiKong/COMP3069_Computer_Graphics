#version 330 core
in vec3 col;
out vec4 fragColour;

void main()
{
	fragColour = vec4(col, 1.0f);
}
