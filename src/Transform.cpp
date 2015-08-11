
#include "vv/Transform.h"

namespace vv
{
  /////////////////////////////////////////////////////////////////////// public
  Transform::Transform()
  {
    homogeneous_transform_mat_ = glm::mat4(1.0f);
  }


  Transform::Transform(Transform const &trans)
  {
    this->homogeneous_transform_mat_ = trans.homogeneous_transform_mat_;
  }


  Transform::Transform(glm::mat4 trans)
  {
    this->homogeneous_transform_mat_ = trans;
  }


  void Transform::translate(glm::vec3 translation)
  {
    homogeneous_transform_mat_ = glm::translate(homogeneous_transform_mat_, translation);
  }


  void Transform::rotate(float angle, glm::vec3 axis)
  {
    homogeneous_transform_mat_ = glm::rotate(homogeneous_transform_mat_, angle, axis);
  }


  void Transform::scale(glm::vec3 scaling)
  {
    homogeneous_transform_mat_ = glm::scale(homogeneous_transform_mat_, scaling);
  }


  glm::mat4 Transform::getMatrix()
  {
    return homogeneous_transform_mat_;
  }


  glm::vec3 Transform::getTranslation()
  {
    glm::vec4 trans = homogeneous_transform_mat_[3];
    return glm::vec3(trans.x, trans.y, trans.z);
  }


  glm::mat3 Transform::getRotation()
  {
    glm::mat3 rot;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        rot[i][j] = homogeneous_transform_mat_[i][j];

    return rot;
  }
} // namespace vv