#version 450

in vec4 v_Color;
in vec4 v_Position;

in vec4 c0;
in vec4 c1;
in vec3 v3Direction;

float g = -0.990f;
vec3 v3LightDirection = vec3 (1.f, 0.0f, 0.0f);

out vec4 FragColor;

float getRayleighPhase(float fCos2)
{
	return 0.75 + 0.75*fCos2;
}

float getMiePhase(float fCos, float fCos2, float g, float g2)
{
	return 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos2) / pow(1.0 + g2 - 2.0*g*fCos, 1.5);
}

void main()
{	
	float g2 = g * g;
	float fcos = dot(v3LightDirection, v3Direction) / length(v3Direction);
	float fcos2 = fcos * fcos;
	
	vec4 color = getRayleighPhase(fcos2) * c0 + getMiePhase(fcos, fcos2, g, g2) * c1;

	color.a = color.b;
	FragColor = color;

}