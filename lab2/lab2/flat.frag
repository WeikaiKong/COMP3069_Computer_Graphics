#version 330 core
out vec4 fragColour;

in vec3 col;
in vec3 pos;

uniform float grey_level;
void main()
{
	if(pos.y > 0)
	{
		fragColour = vec4(1.0f, 0.0f, 0.f, 1.0f);
	}
	else
	{
		fragColour = vec4(0.0f, 0.0f, 1.f, 1.0f);
	}
}
