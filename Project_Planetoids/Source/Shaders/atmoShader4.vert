#version 450

in vec4 position;
//in vec4 normal;
//in vec4 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
//uniform float wavelength;
uniform vec3 cameraPos;

out vec4 v_Color;
//out vec4 v_Position;
//out vec4 v_Normal;
out vec3 c0;
out vec3 c1;
out vec3 v3Direction;

const float PI = 3.141592654;

//------------------------------------
float Kr = 0.0025f;
float Km = 0.0010f;
float ESun = 2000.f;
float fExposure = 2.f;

float fInnerRadius = 6400.f;
float fOuterRadius = fInnerRadius * 1.025;
float fInnerRadius2 = pow(fInnerRadius, 2);
float fOuterRadius2 = pow(fOuterRadius, 2);

float fKrESun = Kr * ESun;
float fKmESun = Km * ESun;

float fKr4PI = Kr * 4 * PI;
float fKm4pi = Km * 4 * PI;

float fScale = 1 / (fOuterRadius - fInnerRadius); // 0.00626
float fScaleDepth = .25f;				   
float fScaleOverScaleDepth = fScale / fScaleDepth; // 0.025

int nSamples = 3;
float fSamples = 3.0;

vec3 v3LightDirection = vec3(0.f, 0.f, 1.f);
vec3 v3InvWaveLength = 1/ vec3(pow(.650, 4), pow(.570, 4), pow(.475, 4));
//------------------------------------

float scale(float fCos)
{
	float x = 1.0 - fCos;
	return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}

void main()
{
    gl_Position = projection * view * model * position;
	vec4 v_Position = view * model * position;
	//v_Normal = normalize(transpose(inverse(model)) * normal);
	vec3 v3CameraPos = cameraPos;
	float fCameraHeight = (length(v3CameraPos) - fInnerRadius);// / (fOuterRadius - fInnerRadius);
	//------------------------------------
	
	vec3 v3Pos = (model * position).xyz;
	vec3 v3Ray = (v3Pos - v3CameraPos).xyz;
	float fFar = length(v3Ray);
	v3Ray /= fFar;
	
	vec3 v3Start = v3CameraPos;
	float fHeight = length(v3Start);// / (fOuterRadius - fInnerRadius);
	float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fCameraHeight));
	float fStartAngle = dot(v3Ray, v3Start) / fCameraHeight;
	float fStartOffset = fDepth * scale(fStartAngle);
	
	float fSampleLength = fFar / 2.0;
	float fScaledLength = fSampleLength * fScale;
	vec3 v3SampleRay = v3Ray * fSampleLength;
	vec3 v3SamplePoint = v3Start * v3SampleRay * .5;
	
	vec3 v3FrontColor = vec3(0.0, 0.0, 0.0);
	for(int i = 0; i < nSamples; i++)
	{
		float fheight = length(v3SamplePoint);// / (fOuterRadius - fInnerRadius);
		float fdepth = exp(fScaleOverScaleDepth * (fInnerRadius - fheight));
		float fLightAngle = dot(v3LightDirection, v3SamplePoint) / fheight;
		float fCameraAngle = dot(v3Ray, v3SamplePoint) / fheight;
		float fScatter = (fStartOffset + fdepth * (scale(fLightAngle) - scale(fCameraAngle)));
		vec3 v3Attenuate = exp(-fScatter * (v3InvWaveLength * fKr4PI + fKm4pi));
		v3FrontColor += v3Attenuate * (fdepth * fScaledLength);
		v3SamplePoint += v3SampleRay;
	}
	c1.rgb = v3FrontColor * fKmESun;
	c0.rgb = v3FrontColor * (v3InvWaveLength * fKrESun);
	//v_Color = vec4(fCameraHeight/255, fCameraHeight/255, fCameraHeight/255, 1);
	v3Direction = v3CameraPos - v3Pos;
	//------------------------------------
	
	
	//float dist = distance(v_Position.xyz, gl_Position.xyz);
	
	//v_Color = vec4(0.0, 0.0, .2, 1.0);
}