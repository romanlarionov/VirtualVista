
#ifndef VIRTUALVISTA_ENTITY_H
#define VIRTUALVISTA_ENTITY_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace vv
{
  class Entity
  {
  public:
    Entity();
    ~Entity();

    void translate(glm::vec3 translation);
    void rotate(float angle, glm::vec3 axis);
    void scale(glm::vec3 scaling);

  protected:
    glm::mat4 model_mat_;

    glm::vec3 position_world_coords_;
  };
}

#endif // VIRTUALVISTA_ENTITY_H