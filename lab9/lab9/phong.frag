#version 330 core

in vec3 col;
in vec3 nor;
in vec3 FragPos;

uniform vec3 lightColour;
uniform vec3 lightDirection;
uniform vec3 lightPos;
uniform vec3 camPos;

out vec4 fragColour;
/*
float CalculateDirectionalIllumination()
{
	float amb = 0.1f;

	vec3 Nnor = normalize(nor);
	vec3 Ntolight = normalize(-lightDirection);
	float diff = max(dot(Nnor, Ntolight), 0.f);

	vec3 Nfromlight = normalize(lightDirection);
	vec3 refDir = reflect(Nfromlight, Nnor);
	vec3 camDir = normalize(camPos - FragPos);
	float spec = pow(max(dot(camDir, refDir), 0.f), 128);

	float i = amb + diff + spec;

	return i;
}
*/
/*
float CalculatePositionalIllumination()
{
	float amb = 0.1f;

	vec3 Nnor = normalize(nor);
	vec3 NToLight = normalize(lightPos - FragPos);
	float diff = max(dot(Nnor, NToLight), 0.f);

	vec3 NFromLight = -NToLight;
	vec3 refDir = reflect(NFromLight, Nnor);
	vec3 NcamDir = normalize(camPos - FragPos);
	float spec = pow(max(dot(NcamDir, refDir), 0.f), 128);

	float d = length(lightPos - FragPos);
	float c = 1.5f;
	float l = .05f;
	float q = .02f;
	float att = 1.f / (c + (l*d) + (q*(d*d)));

	float i = (amb + diff + spec) * att;

	return i;
}
*/

float CalculateSpotIllumination()
{
	float amb = 0.1f;

	vec3 Nnor = normalize(nor);
	vec3 NToLight = normalize(lightPos - FragPos);
	float diff = max(dot(Nnor, NToLight), 0.f);

	vec3 NFromLight = -NToLight;
	vec3 refDir = reflect(NFromLight, Nnor);
	vec3 NcamDir = normalize(camPos - FragPos);
	float spec = pow(max(dot(NcamDir, refDir), 0.f), 128);

	float d = length(lightPos - FragPos);
	float c = 1.5f;
	float l = .05f;
	float q = .02f;
	float att = 1.f / (c + (l*d) + (q*(d*d)));

	float phi = cos(radians(15.f));
	vec3 NSpotDir = normalize(lightDirection);
	float theta = dot(NFromLight, NSpotDir);

	float i;
	if(theta > phi)
	{
		i = (amb + diff + spec) * att;
	}
	else
	{
		i = (amb) * att;
	}

	return i;
}
void main()
{
	//fragColour = vec4(col, 1.f);
	//float phong = CalculateDirectionalIllumination();
	//float phong = CalculatePositionalIllumination();
	float phong = CalculateSpotIllumination();
	fragColour = vec4(phong * col * lightColour, 1.f);
}
 