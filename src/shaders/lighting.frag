#version 330 core

uniform sampler2D texture_diffuse1;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 view_position;

in vec2 Tex_Coord;
in vec3 Normal;
in vec3 Frag_Position;

out vec4 color;

void main()
{
  float ambient_strength = 0.2f;

  vec3 unit_normal = normalize(Normal);
  vec3 unit_light_direction = normalize(light_position - Frag_Position);
  float diffuse_strength = max(dot(unit_light_direction, unit_normal), 0.0f);

  float specular_intensity = 0.5f;
  float shininess = 64;
  vec3 view_direction = normalize(view_position - Frag_Position);
  vec3 reflection_direction = reflect(-unit_light_direction, unit_normal);
  float specular_strength = specular_intensity * pow(max(dot(view_direction, reflection_direction), 0.0f), shininess);

  vec4 final_light_color = vec4((ambient_strength + diffuse_strength + specular_strength) * light_color, 1.0f);
  color = final_light_color * texture(texture_diffuse1, Tex_Coord);
}