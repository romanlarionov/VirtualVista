#version 330 core

struct Light
{
  vec3 position;
  vec3 color;
};

const int NUM_LIGHTS = 16;

uniform Light lights[NUM_LIGHTS];
uniform sampler2D texture_diffuse1;
uniform vec3 view_position;

in vec2 Tex_Coord;
in vec3 Normal;
in vec3 Frag_Position;

out vec4 color;

void main()
{
  float ambient_strength = 0.2f;
  float specular_intensity = 0.5f;
  float shininess = 32;

  vec3 unit_normal = normalize(Normal);
  vec3 view_direction = normalize(view_position - Frag_Position);
  vec3 final_light_color = vec3(ambient_strength);

  for (int i = 0; i < NUM_LIGHTS; ++i)
  {
    vec3 unit_light_direction = normalize(lights[i].position - Frag_Position);
    vec3 halfway_direction = normalize(unit_light_direction + view_direction);

    float diffuse_strength = max(dot(unit_light_direction, unit_normal), 0.0f);
    float specular_strength = specular_intensity * pow(max(dot(unit_normal, halfway_direction), 0.0f), shininess);

    final_light_color += vec3((diffuse_strength + specular_strength) * lights[i].color);
  }

  color = vec4(final_light_color, 1.0f) * texture(texture_diffuse1, Tex_Coord);
}