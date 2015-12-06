
#ifndef VIRTUALVISTA_TRANSFORM_H
#define VIRTUALVISTA_TRANSFORM_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

namespace vv
{
  class Transform
  {
  public:
    Transform();
    Transform(Transform const &trans);
    Transform(glm::mat4 trans);

    void translate(glm::vec3 translation);
    void rotate(float angle, glm::vec3 axis);
    void scale(glm::vec3 scaling);

    glm::mat4 getMatrix();
    glm::vec3 getPosition();
    glm::mat3 getOrientation();

  private:
    glm::mat4 homogeneous_transform_mat_;
  };
}

#endif // VIRTUALVISTA_TRANSFORM_H