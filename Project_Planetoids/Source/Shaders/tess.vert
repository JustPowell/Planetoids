#version 450

in vec4 position;
in vec3 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 cameraPos;

out VS_OUT
{
	vec4 color;
	vec4 position;
	vec3 camPos;
} vs_out;

void main()
{
    gl_Position = projection * view * model * position;
	vs_out.camPos = (inverse(model) * vec4(cameraPos,1)).xyz;
	vs_out.color = vec4(color, 1.f);//vec4(0.f, .6f, 1.f, 1.f);
	vs_out.position = position;
}