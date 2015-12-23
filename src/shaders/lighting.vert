#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 Tex_Coord;
out vec3 Normal;
out vec3 Frag_Position;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    Normal = mat3(transpose(inverse(model))) * normal;
    Frag_Position = vec3(model * vec4(position, 1.0f));
    Tex_Coord = tex_coord;
}