#version 450

in GE_OUT
{
	flat vec4 color;
	vec4 position;
	vec3 normal;
	float noise;
}ge_in;

out vec4 FragColor;

void main()
{	
	vec3 normal = normalize(vec3(ge_in.normal));
	vec3 lightd = normalize(vec3(0, 0, 1) - vec3(ge_in.position.xyz));
	float nDotL = abs(dot(lightd, ge_in.normal));
	vec3 ambient = vec3(.2, .2, .2) * vec3(1.0, 1.0, 1.0);
	vec3 diffuse = ge_in.color.rgb * vec3(1.0, 1.0, 1.0) * nDotL;
	FragColor = vec4((diffuse + ambient) * ge_in.color.xyz, 1.0);
}