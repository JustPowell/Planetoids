#version 450

in vec4 v_Color;
in vec4 v_Position;
in vec4 v_Normal;
in vec4 c0;
in vec4 c1;


out vec4 FragColor;

void main()
{	
	
	vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
	vec3 normal = normalize(vec3(v_Normal));
	vec3 lightDirection = normalize(vec3(-1000000.0, 0.0, 0.0) - vec3(v_Position));
	float nDotL = max(dot(lightDirection, normal), 0);
	vec3 ambient = vec3(0.1, 0.1, 0.1);
	vec3 diffuse = color.rgb * nDotL;
    FragColor = (vec4((diffuse + ambient) * (v_Color.rgb), v_Color.a)) + (.25 * c1);
	//FragColor = color;
	//gl_FragColor = v_color;
}