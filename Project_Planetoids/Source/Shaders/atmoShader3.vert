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
const float p  = 1;
 
float log2_e = 1.0/log(2.0);
const float e = 2.71828;
const float PI = 3.141592654;

vec4 lambda2rgb(float lambda);

float Fr(float theta)
{
	return (3/4)*(1 + pow(cos(theta), 2));
}

float P(float h)
{
	return exp(-h/.25);
}

float B(float lambda, float k)
{
	return (4*PI*k)/pow(lambda, 4);
}

float Fm(float theta)
{
	float g = -0.990f;
	return (1-pow(g, 2)) / pow((1 + pow(g, 2) - 2*g*cos(theta)), (3/2));
}

vec4 rayleigh(float lambda, float theta)
{
	vec4 color = lambda2rgb(lambda);
	return (color * K * Fr(theta)) / pow(lambda, 4);
}

void main()
{
    gl_Position = projection * view * model * position;
	v_Position = view * model * position;
	v_Normal = normalize(transpose(inverse(model)) * normal);
	
	vec4 color;
	for(int i = 380; i < 780; i+=10)
	{
		color += lambda2rgb(i);
	}
	
	float m = max(max(color.r, color.g), color.b);
	color /= m;
	v_Color = color;
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