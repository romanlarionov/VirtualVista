
#ifndef VIRTUALVISTA_LIGHT_H
#define VIRTUALVISTA_LIGHT_H

#include <set>

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"

namespace vv
{
  class Light
  {
  public:
    Light(bool point_light = true);
    ~Light();

    Transform* getTransform();

    void update(Shader *shader);

    // renders a cube that represents the light
    void render();

  private:
    Transform *transform_;

    static std::set<Light *> lights_;

    Mesh *cube_mesh_;

    bool is_point_light_;

    glm::vec3 color_;
    GLfloat intensity_;
    glm::vec3 direction_;
 };
}

#endif  // VIRTUALVISTA_LIGHT_H