#version 450

in GS_OUT
{
	flat vec4 color[4];
}fs_in;

out vec4 FragColor;
void main()
{	
	FragColor = vec4(0, .6, 1., 1.);//fs_in.color[0];
}