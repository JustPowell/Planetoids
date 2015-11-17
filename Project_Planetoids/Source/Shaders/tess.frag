#version 450

in GE_OUT
{
	flat vec4 color;

}ge_in;

out vec4 FragColor;

void main()
{	
	
	FragColor = ge_in.color;
}