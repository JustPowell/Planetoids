#version 450

in vec4 position;
in vec4 normal;
in vec4 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 cameraPos;

uniform float Kr;// = .0025f;// = 0.0025f;
uniform float Km;// = .001f;// = 0.0020f;
uniform float ESun;// = 30.f;// = 10.f;
uniform vec3 v3InvWaveLength;// = 1/ vec3(pow(.650, 4), pow(.570, 4), pow(.475, 4));

const float PI = 3.141592654;
uniform float fInnerRadius;// = 10.f;
float fOuterRadius = fInnerRadius * 1.025;
float fInnerRadius2 = pow(fInnerRadius, 2);
float fOuterRadius2 = pow(fOuterRadius, 2);

float fKrESun = Kr * ESun;
float fKmESun = Km * ESun;
float fKr4PI = Kr * 4 * PI;
float fKm4pi = Km * 4 * PI;

float fScale = 1.0 / (fOuterRadius - fInnerRadius); // 0.00626
float fScaleDepth = .25f;				   
float fScaleOverScaleDepth = fScale / fScaleDepth; // 0.025

uniform int nSamples;
float fSamples = float(nSamples);
vec3 sunPos = vec3(4776.f, 0.f, 0.f);
vec3 v3LightDirection = normalize(sunPos - vec3(0.f, 0.f, 0.f));//vec3(1.f, 0.f, 0.f);

out vec4 v_Color;
out vec4 v_Position;
out vec4 v_Normal;
out vec4 c0;
out vec4 c1;

float scale(float fCos)
{
	float x = 1.0 - fCos;
	return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}

float getNearIntersection(vec3 v3Pos, vec3 v3Ray, float fDistance2, float fRadius2)
{
	float B = 2.0 * dot(v3Pos, v3Ray);
	float C = fDistance2 - fRadius2;
	float fDet = max(0.0, B*B - 4.0 * C);
	return 0.5 * (-B - sqrt(fDet));
}

void main()
{
    gl_Position = projection * view * model * position;
	v_Position = model * position;
	v_Normal = normalize(transpose(inverse(model)) * normal);
	//v_Color = color;
	v_Color = vec4(0, .361, .0353, 1.0);
	vec3 v3CameraPos = (inverse(model) * vec4(cameraPos,1)).xyz;
	//---------------------------------------------------------------
	
	float fCameraHeight = length(v3CameraPos);
	vec3 v3pos = position.xyz;
	vec3 v3ray = v3pos - v3CameraPos;
	float fFar = length(v3ray);
	v3ray /= fFar;
	
	float fNear = getNearIntersection(v3CameraPos, v3ray, pow(fCameraHeight, 2), fOuterRadius2);
	
	vec3 v3start = v3CameraPos + v3ray * fNear;
	fFar -= fNear;
	float fdepth = exp((fInnerRadius - fCameraHeight) / fScaleDepth);
	float fCameraAngle = dot(-v3ray, v3pos) / length(v3pos);
	float fLightAngle = dot(v3LightDirection, v3pos) / length(v3pos);
	float fCameraScale = scale(fCameraAngle);
	float fLightScale = scale(fLightAngle);
	float fCameraOffset = fdepth * fCameraScale;
	float fTemp = (fLightScale + fCameraScale);
	
	float fSampleLength = fFar / fSamples;
	float fScaledLength = fSampleLength * fScale;
	vec3 v3SampleRay = v3ray * fSampleLength;
	vec3 v3SamplePoint = v3start + v3SampleRay * .5;
	
	vec3 v3FrontColor = vec3(0.0, 0.0, 0.0);
	vec3 v3Attenuate;
	for(int i = 0; i < nSamples; i++)
	{
		float fHeight = length(v3SamplePoint);
		float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
		float fScatter = fDepth*fTemp - fCameraOffset;
		v3Attenuate = exp(-fScatter * (v3InvWaveLength * fKr4PI + fKm4pi));
		v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
		v3SamplePoint += v3SampleRay;
	}
	
	c0.rgb = v3FrontColor * (v3InvWaveLength * fKrESun + fKmESun);
	//v_Color += (.1 *c0);
	c1.rgb = v3Attenuate;
}