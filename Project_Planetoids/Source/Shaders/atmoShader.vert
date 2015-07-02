#version 450

in vec4 position;
in vec4 normal;
in vec4 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 cameraPos;
uniform float wavelength;

out vec4 v_Color;
out vec4 v_Position;
out vec4 v_Normal;

const float Ns = 2.545e25;
const float n  = 1.000278;
const float K  = ((2*3.14159) * pow(pow(n, 2) - 1, 2)) / (3 * Ns);
const float pr = 6400.f;
const float ar = pr + 200;
const float p  = 1;

const vec3 Br = vec3(6.95e-6, 1.18e-5, 2.44e-5);
const vec3 Bm = vec3(4e-7, 6e-7, 2.4e-6);
const vec3 Brm = Br+Bm;
const vec4 Esun = vec4(1.0, 1.0, 1.0, 30.0);
const float g = 0.0;
 
float log2_e = 1.0/log(2.0);
const float e = 2.71828;
const float PI = 3.141592654;

vec3 Fex(float s)
{
    vec3 ex = exp(Brm * -s);
    return ex;
}
 
vec3 rayleigh(float theta)
{
    float pi316 = 3.0/(8.0*PI);
 
    float phase = 1.0 + (theta*theta);
     
    vec3 ret = pi316*phase*Br;
    return ret;
}
 
vec3 mie(float theta)
{
    float pi14 = 1.0/(4.0*PI);
 
    float g1 = (1.0-g)*(1.0-g);
    float g2 = 1.0+(g*g);
    float g3 = 2.0*g;
 
    float phase = g1 / pow(g2 - g3*theta, 1.5);
     
    vec3 ret = pi14*phase*Bm;
    return ret;
}
 
vec3 inScatter(float s, float theta)
{
    vec3 num = rayleigh(theta) + mie(theta);
    num *= Esun.w;
    num *= 1.0-Fex(s);
 
    vec3 ret = num/Brm;
    return ret;
}

vec4 lambda2rgb(float lambda)
{
	vec4 color;
	if(lambda >= 380.0 && lambda <= 439.0)
	{
		color.r = -(lambda - 440.0) / (440.0 - 380.0);
		color.g = 0.0;
		color.b = 1.0;
	}
	else if(lambda > 439.0 && lambda <= 489.0)
	{
		color.r = 0.0;
		color.g = (lambda - 440.0) / (490.0 - 440.0);
		color.b = 1.0;
	}
	else if(lambda > 489.0 && lambda <= 509.0)
	{
		color.r = 0.0;
		color.g = 1.0;
		color.b = -(lambda - 510.0) / (510.0 - 490.0);
	}
	else if(lambda > 509.0 && lambda <= 579.0)
	{
		color.r = (lambda - 510.0) / (580.0 - 510.0);
		color.g = 1.0;
		color.b = 0.0;
	}
	else if(lambda > 579.0 && lambda <= 644.0)
	{
		color.r = 1.0;
		color.g = -(lambda - 645.0) / (645.0 - 580.0);
		color.b = 0.0;
	}
	else if(lambda > 644.0 && lambda <= 780.0)
	{
		color.r = 1.0;
		color.g = 0.0;
		color.b = 0.0;
	}
	else
	{
		color.r = 0.0;
		color.g = 0.0;
		color.b = 0.0;
	}
	
	if (lambda >= 380.0 && lambda <= 419.0)
	{
		color.a = ((lambda - 380.0) / (420.0 - 380.0));
	}
	else if (lambda > 419.0 && lambda <= 700.0)
	{
		color.a = 1.0;
	}
	else if (lambda > 700.0 && lambda <= 780.0)
	{
		color.a = ((780.0 - lambda) / (780.0 - 700.0));
	}
	else
	{
		color.a = 0.0;
	}

	return color;
}

void main()
{
    gl_Position = projection * view * model * position;
	v_Position = view * model * position;
	v_Normal = normalize(transpose(inverse(model)) * normal);
	float dist = distance(v_Position.xyz, gl_Position.xyz);
	/*
	vec4 rgb = lambda2rgb(rgb2);*/
	
	vec3 scattering = inScatter(dist, dot(normal.xyz, normalize(vec3(1, -1, 1))));
	vec3 extinction = Fex(dist);
	vec3 light = vec3(1, -1, 1);
	vec4 rgb = (vec4(0.0, 0.0, 0.0, 1.0)*vec4(extinction, 1.0)) + vec4(scattering, 1.0);
	v_Color = rgb;
}