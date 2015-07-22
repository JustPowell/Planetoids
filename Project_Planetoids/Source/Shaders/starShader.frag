#version 450

in vec4 v_Color;
in vec4 v_Position;
in vec4 v_Normal;

out vec4 FragColor;

void main()
{
	FragColor = v_Color;
}