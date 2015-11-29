#version 450

in GE_OUT
{
	flat vec4 color;
	vec4 position;
	vec3 normal;
	float noise;
}ge_in;

in vec3 gTriDistance;
in vec4 gPatchDistance;

out vec4 FragColor;

vec3 InnerLineColor = vec3(1, 1, 1);
float amplify(float d, float scale, float offset)
{
    d = scale * d + offset;
    d = clamp(d, 0, 1);
    d = 1 - exp2(-2*d*d);
    return d;
}

void main()
{	
	vec3 normal = normalize(vec3(ge_in.normal));
	vec3 lightd = normalize(vec3(0, 0, 1000000) - vec3(ge_in.position.xyz));
	float nDotL = abs(dot(lightd, ge_in.normal));
	vec3 ambient = vec3(.2, .2, .2) * vec3(1.0, 1.0, 1.0);
	vec3 diffuse = ge_in.color.rgb * vec3(1.0, 1.0, 1.0) * nDotL;
	
	float d1 = min(min(gTriDistance.x, gTriDistance.y), gTriDistance.z);
	float d2 = min(min(min(gPatchDistance.x, gPatchDistance.y), gPatchDistance.z), gPatchDistance.w);
	d1 = 1 - amplify(d1, 25, -.50);
	d2 = amplify(d2, 500, -0.50);
	
	
	vec3 col = vec3((diffuse + ambient) * (ge_in.color.xyz));
	if(true){
		FragColor = vec4(d2 * col + d1 * d2 * InnerLineColor, 1.0);
	}
	else{
		FragColor = vec4(col, 1.0);
	}
	
}