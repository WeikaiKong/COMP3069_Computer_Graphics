#version 330 core
uniform float grey_level;
in vec3 col;
out vec4 fragColour;
void main()
{
	fragColour = vec4(grey_level, grey_level, grey_level, 1.0f);
	//fragColour = vec4(col, 1.0f);
};