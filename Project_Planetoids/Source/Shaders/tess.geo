#version 450

layout(triangles, invocations = 3) in;
layout(triangle_strip, max_vertices = 4) out;

in TES_OUT
{
	vec4 color;
	vec4 position;
	vec3 normal;
	float noise;
} tes_in[];

in vec4 tePatchDistance[3];

out GE_OUT
{
	vec4 color;
	vec4 position;
	vec3 normal;
	float noise;
} ge_out;

out vec4 gPatchDistance;
out vec3 gTriDistance;

void main()
{
	gl_Position = gl_in[0].gl_Position;
	ge_out.position = tes_in[0].position;
	ge_out.color = tes_in[0].color;
	ge_out.normal = tes_in[0].normal;
	ge_out.noise = tes_in[0].noise;
	gPatchDistance = tePatchDistance[0];
	gTriDistance = vec3(1, 0, 0);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	ge_out.position = tes_in[1].position;
	ge_out.color = tes_in[1].color;
	ge_out.normal = tes_in[1].normal;
	ge_out.noise = tes_in[1].noise;
	gPatchDistance = tePatchDistance[1];
	gTriDistance = vec3(0, 1, 0);
	EmitVertex();
	
	gl_Position = gl_in[2].gl_Position;
	ge_out.position = tes_in[2].position;
	ge_out.color = tes_in[2].color;
	ge_out.normal = tes_in[2].normal;
	ge_out.noise = tes_in[2].noise;
	gPatchDistance = tePatchDistance[2];
	gTriDistance = vec3(0, 0, 1);
	EmitVertex();
	EndPrimitive();
	
}