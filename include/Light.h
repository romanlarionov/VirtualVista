
#ifndef VIRTUALVISTA_LIGHT_H
#define VIRTUALVISTA_LIGHT_H

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include "Entity.h"
#include "Mesh.h"
#include "Shader.h"

namespace vv
{
  class Light : public Entity
  {
  public:
    Light(bool point_light = true);
    ~Light();

    void update(Shader *shader);

    // renders a cube that represents the light
    void render();

  private:
    Mesh *cube_mesh_;

    bool is_point_light_;

    glm::vec3 color_;
    GLfloat intensity_;
    glm::vec3 direction_;
 };
}

#endif  // VIRTUALVISTA_LIGHT_H