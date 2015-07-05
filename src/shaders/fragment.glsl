#version 330 core

in vec3 pos;

out vec4 color;

void main()
{
    color = vec4(pos, 1.0);
}
