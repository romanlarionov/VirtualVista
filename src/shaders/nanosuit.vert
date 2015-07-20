#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 tex_coords;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    tex_coords = tex_coord;
}