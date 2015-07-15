#version 450

in vec4 v_Color;
in vec4 v_Position;
//in vec4 v_Normal;
in vec4 c0;
in vec4 c1;
in vec3 v3Direction;
in float cameraHeight;
float g = -0.990f;
vec3 v3LightDirection = vec3 (1.f, 0.0f, 0.0f);
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
	vec3 v3InvWaveLength = 1/ vec3(pow(.650, 4), pow(.570, 4), pow(.475, 4));
	vec4 color = getRayleighPhase(fcos2) * c0 + getMiePhase(fcos, fcos2, g, g2) * c1;
	//vec4 color = getRayleighPhase(fcos2) * (vec4(v3InvWaveLength, 0) * .05) + getMiePhase(fcos, fcos2, g, g2) * (vec4(v3InvWaveLength, 0) * .05);
	/*if(color.r < 0 || color.r > 1)
	{
		color.r = 1.0;
	}
	if(color.g < 0 || color.r > 1)
	{
		color.g = 1.0;
	}
	if(color.b < 0 || color.r > 1)
	{
		color.b = 1.0;
	}*/
	color.a = color.b;
	FragColor = color;
	//FragColor = v_Color;
	
	//FragColor = vec4(1.0, 1, 0, 1.0);
	//FragColor = vec4(1, 1, 1, 1.f-(cameraHeight));
}