#version 450

layout(triangles, invocations = 3) in;
layout(triangle_strip, max_vertices = 4) out;

in TES_OUT
{
	vec4 color;
} tes_in[];

out GE_OUT
{
	vec4 color;
} ge_out;

void main()
{
	gl_Position = gl_in[0].gl_Position;
	ge_out.color = tes_in[0].color;

	EmitVertex();
	gl_Position = gl_in[1].gl_Position;
	//ge_out.color = tes_in[1].color;

	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	//ge_out.color = tes_in[2].color;

	EmitVertex();
	EndPrimitive();
	
}