
#ifndef VIRTUALVISTA_LIGHT_H
#define VIRTUALVISTA_LIGHT_H

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include "Mesh.h"
#include "Shader.h"

namespace vv
{
  class Light
  {
  public:
    Light(bool point_light = true);
    ~Light();

    void translate(glm::vec3 translation);
    void rotate(float angle, glm::vec3 axis);
    void scale(glm::vec3 scaling);

    void update();

    // renders a cube that represents the light
    void render();

  private:
    Mesh *cube_mesh_;
    glm::mat4 model_mat_;

    GLuint VAO_;
    GLuint VBO_;

    glm::vec3 position_;
    glm::vec3 color_;

    bool is_point_light_;
 };
}
#endif      //VIRTUALVISTA_LIGHT_H