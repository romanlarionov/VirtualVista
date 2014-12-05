
#version 150

in vec3 position;

out vec3 fPosition;

void main()
{
	fPosition = position;
    gl_Position = vec4(position, 1.0);
}