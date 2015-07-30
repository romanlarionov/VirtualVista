
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Entity.h"

namespace vv
{
  Entity::Entity()
  {
    model_mat_ = glm::mat4(1.0f);
    position_world_coords_ = glm::vec3(0.0f, 0.0f, 0.0f);
  }


  Entity::~Entity()
  {
  }


  void Entity::translate(glm::vec3 translation)
  {
    model_mat_ = glm::translate(model_mat_, translation);
    position_world_coords_ += translation;
  }


  void Entity::rotate(float angle, glm::vec3 axis)
  {
    model_mat_ = glm::rotate(model_mat_, angle, axis);
  }


  void Entity::scale(glm::vec3 scaling)
  {
    model_mat_ = glm::scale(model_mat_, scaling);
  }
} // namespace vv