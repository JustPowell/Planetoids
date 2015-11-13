#version 450

in GE_OUT
{
	flat vec4 color;
	vec3 gPatchDist;
	vec3 gTriDist;
}ge_in;

out vec4 FragColor;

float amplify(float d, float scale, float offset)
{
	d = scale * d + offset;
    d = clamp(d, 0, 1);
    d = 1 - exp2(-2*d*d);
    return d;
}

void main()
{	
	/*float d1 = min(min(ge_in.gTriDist.x, ge_in.gTriDist.y), ge_in.gTriDist.z);
	float d2 = min(min(ge_in.gPatchDist.x, ge_in.gPatchDist.y), ge_in.gPatchDist.z);
	vec3 color = amplify(d1, 10, -0.5) * amplify(d2, 60, -0.5) * ge_in.color.xyz;
*/
	FragColor = ge_in.color;
}