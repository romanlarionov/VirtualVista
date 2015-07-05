
#include "Camera.h"
#include "Input.h"

namespace vv
{
  Camera::Camera(Shader* shader) :
    pitch_angle_(0),
    yaw_angle_(0),
    max_pitch_angle_(1),
    max_yaw_angle_(1),
    shader_(*shader)
  {
    up_vec_ = glm::vec3(0, 1, 0);
    position_vec_ = glm::vec3(0, 0, 3);
    look_at_vec_ = glm::vec3(0, 0, 0);
    position_delta_ = glm::vec3(0, 0, 0);
  }

  void Camera::update()
  {
    // compute helper vectors
    direction_vec_ = glm::normalize(look_at_vec_ - position_vec_);
    glm::vec3 right_vec = glm::cross(direction_vec_, up_vec_);

    // find component-wise rotation quaternions
    glm::quat pitch_quat = glm::angleAxis(pitch_angle_, right_vec);
    glm::quat yaw_quat = glm::angleAxis(yaw_angle_, up_vec_);

    // combine both components
    glm::quat combined_rotations = glm::normalize(glm::cross(pitch_quat, yaw_quat));

    // perform rotation and store
    direction_vec_ = glm::rotate(combined_rotations, direction_vec_);
    position_vec_ += position_delta_;
    position_delta_ = glm::vec3(0, 0, 0);
    look_at_vec_ = position_vec_ + direction_vec_ * 1.0f;
    pitch_angle_ = 0;
    yaw_angle_ = 0;
  }

  void Camera::move(GLint key, double movement_speed)
  {
    switch (key)
    {
      case GLFW_KEY_W: position_delta_ += direction_vec_ * float(movement_speed);
                       break;
      case GLFW_KEY_S: position_delta_ += direction_vec_ * float(movement_speed);
                       break;
      case GLFW_KEY_D: position_delta_ += direction_vec_ * float(movement_speed);
                       break;
      case GLFW_KEY_A: position_delta_ += direction_vec_ * float(movement_speed);
                       break;
      default: break;
    }
  }

  void Camera::rotate(double x, double y, double rotation_speed)
  {
    x *= rotation_speed;
    y *= rotation_speed;

    // yaw
    if (x < -max_yaw_angle_)     x = -max_yaw_angle_;
    else if (x > max_yaw_angle_) x = max_yaw_angle_;

    yaw_angle_ -= x;

    // put bounds on the yaw for a more natural fps camera feeling
//    if (((pitch_angle_ >  90) && (pitch_angle_ <  270)) ||
//        ((pitch_angle_ < -90) && (pitch_angle_ > -270)))
//      yaw_angle_ -= x;
//    else
//      yaw_angle_ += x;

//    if (yaw_angle_ > 360.0f)
//      yaw_angle_ -= 360.0f;
//    else if (yaw_angle_ < -360.0f)
//      yaw_angle_ += 360.0f;

  // pitch
    if (y < -max_pitch_angle_)
      y = -max_pitch_angle_;
    else if (y > max_pitch_angle_)
      y = max_pitch_angle_;

    pitch_angle_ += y;

    if (pitch_angle_ > 89.0f)
      pitch_angle_ = 89.0f;
    else if (pitch_angle_ < -89.0f)
      pitch_angle_ = -89.0f;
  }

  void Camera::bindViewMatrix()
  {
    view_mat_ = glm::lookAt(position_vec_, look_at_vec_, up_vec_);
    GLint view_location = glGetUniformLocation(shader_.getProgramId(), "view");
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view_mat_));
  }
} // namespace vv