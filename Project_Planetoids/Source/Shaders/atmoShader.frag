#version 450

in vec4 v_Color;
in vec4 v_Position;
in vec4 v_Normal;
in vec3 scattering;
in vec3 extinction;

out vec4 FragColor;
void main()
{	
	vec3 light = vec3(1, -1, 1);
	//vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
	//vec3 normal = normalize(vec3(v_Normal));
	//vec3 lightDirection = normalize(vec3(0.0, 1.0, 0.0) - vec3(v_Position));
	//float nDotL = max(dot(lightDirection, normal), 0.0);
	//vec3 ambient = vec3(0.2, 0.2, 0.2);
	//vec3 diffuse = color.rgb * nDotL;
    //FragColor = vec4((diffuse + ambient) * v_Color.rgb, v_Color.a);
	//vec4 rgb = (vec4(0.0, 0.0, 0.0, 1.0)*vec4(extinction, 1.0)) + vec4(scattering, 1.0);
	FragColor = v_Color;
}