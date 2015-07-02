#version 450

in vec4 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 nm;

void main()
{
    gl_Position = projection * view * model * position;
}