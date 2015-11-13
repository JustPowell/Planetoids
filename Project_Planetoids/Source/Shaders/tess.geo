#version 450

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in TES_OUT
{
	vec4 color;
	vec3 tePosition;
	vec3 tePatchDist;
} tes_in[];

out GE_OUT
{
	vec4 color;
	vec3 gPatchDist;
	vec3 gTriDist;
} ge_out;

void main()
{
	gl_Position = gl_in[0].gl_Position;
	ge_out.color = tes_in[0].color;
	ge_out.gPatchDist = tes_in[0].tePatchDist;
	ge_out.gTriDist = vec3(1, 0, 0);
	EmitVertex();
	gl_Position = gl_in[1].gl_Position;
	ge_out.color = tes_in[1].color;
	ge_out.gPatchDist = tes_in[1].tePatchDist;
	ge_out.gTriDist = vec3(0, 1, 0);
	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	ge_out.color = tes_in[2].color;
	ge_out.gPatchDist = tes_in[2].tePatchDist;
	ge_out.gTriDist = vec3(0, 0, 1);
	EmitVertex();
	EndPrimitive();
	
}