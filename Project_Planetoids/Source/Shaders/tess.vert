#version 450

in vec4 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VS_OUT
{
	vec4 color;
} vs_out;

void main()
{
    gl_Position = projection * view * model * position;
	vs_out.color = vec4(0, .6, 1., 1.);
}