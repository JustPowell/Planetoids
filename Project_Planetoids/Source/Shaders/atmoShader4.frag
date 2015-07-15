#version 450

in vec4 v_Color;
//in vec4 v_Position;
//in vec4 v_Normal;
in vec3 c0;
in vec3 c1;
in vec3 v3Direction;
float g = -0.990f;
vec3 v3LightDirection = vec3 (0.f, 0.0f, 1.0f);
//uniform float g2 = g*g;

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
	
	vec3 color = getRayleighPhase(fcos2) * c0 + getMiePhase(fcos, fcos2, g, g2) * c1;
	vec4 c = vec4(color.rgb, color.b);
	//color *= -1;
	//color.a = color.b;
	FragColor = c;
	//FragColor = v_Color;
}