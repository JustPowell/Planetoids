#version 450

in vec4 v_Color;
in vec4 v_Position;
in vec4 v_Normal;
in vec3 c0;
in vec3 c1;
in vec3 v3Direction;
float g = -0.990f;
vec3 v3LightPos = vec3 (10000.f, 0.0f, 0.0f);
//uniform float g2 = g*g;

out vec4 FragColor;

float getMiePhase(float fCos, float fCos2, float g, float g2)
{
	return 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos2) / pow(1.0 + g2 - 2.0*g*fCos, 1.5);
}

// Calculates the Rayleigh phase function
float getRayleighPhase(float fCos2)
{
	//return 1.0;
	return 0.75 + 0.75*fCos2;
}

void main()
{	
	float fCos = dot(v3LightPos - v3Direction) / length(v3Direction);
	float fMiePhase = getMiePhase(fcos, pow(fcos, 2), g, pow(g, 2));
	vec4 color = c1 + fMiePhase * c0;
	color.a = color.b;
	FragColor = color;
}