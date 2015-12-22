
#ifndef VIRTUALVISTA_LIGHT_H
#define VIRTUALVISTA_LIGHT_H

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Entity.h"

namespace vv
{
  class Light : public Entity
  {
    friend class Renderer;

  public:
    Light(bool can_render = true, bool point_light = true);
    ~Light();

    void render();

  private:
    Mesh *cube_mesh_;

    bool can_render_;
    bool is_point_light_;

    glm::vec3 color_;
    GLfloat intensity_;
    glm::vec3 direction_;

    void setUniforms(int num, Shader *shader);
 };
}

#endif  // VIRTUALVISTA_LIGHT_H