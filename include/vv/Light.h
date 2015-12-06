
#ifndef VIRTUALVISTA_LIGHT_H
#define VIRTUALVISTA_LIGHT_H

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"

namespace vv
{
  class Light
  {
    friend class Renderer;
  public:
    Light(bool can_render = true, bool point_light = true);
    ~Light();

    bool canRender();
    Transform* getTransform();

    // renders a cube that represents the light
    void render();

  private:
    Transform *transform_;
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