#version 450

in vec4 position;
in vec4 normal;
in vec4 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 v_Position;
out vec4 v_Normal;
out vec4 v_Color;

void main()
{
	gl_Position = projection * view * model * position;
	v_Position = model * position;
	v_Normal = normalize(transpose(inverse(model)) * normal);
	v_Color = vec4(1, 1, 1, 1);
}