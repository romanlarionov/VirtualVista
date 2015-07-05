
#include "Camera.h"
#include "Input.h"

namespace vv
{
  Camera::Camera() :
    field_of_view_(45),  // TODO: change to global settings system
    near_clip_(10),
    far_clip_(100),
    movement_speed_(0.5f),
    rotation_speed_(0.5f),
    max_pitch_angle_(5),
    max_yaw_angle_(5)
  {
    aspect_ratio_ = 800.0 / 600.0;
    up_vec_ = glm::vec3(0, 1, 0);
    position_vec_ = glm::vec3(0, 0, 0);
  }

  void Camera::update()
  {
    // compute helper vectors
    direction_vec_ = glm::normalize(look_at_vec_ - position_vec_);
    glm::vec3 right_vec = glm::cross(direction_vec_, up_vec_);

    this->updatePosition();
    this->updateOrientation();

    // find component-wise rotation quaternions
    glm::quat pitch_quat = glm::angleAxis(pitch_angle_, right_vec);
    glm::quat yaw_quat = glm::angleAxis(yaw_angle_, up_vec_);

    // combine both components
    glm::quat combined_rotations = glm::normalize(glm::cross(pitch_quat, yaw_quat));

    // perform rotation and store
    direction_vec_ = glm::rotate(combined_rotations, direction_vec_);
    look_at_vec_ = position_vec_ + direction_vec_ * 1.0f;

    // compute matrices
    projection_mat_ = glm::perspective(field_of_view_, aspect_ratio_, near_clip_, far_clip_);
    view_mat_ = glm::lookAt(position_vec_, look_at_vec_, up_vec_);
    model_mat_ = glm::mat4(1.0f);
    model_view_projection_mat_ = projection_mat_ * view_mat_ * model_mat_;
  }

  void Camera::updatePosition()
  {
    if (Input::instance()->keyIsPressed(GLFW_KEY_W))
      position_vec_ += direction_vec_ * movement_speed_;

    if (Input::instance()->keyIsPressed(GLFW_KEY_S))
      position_vec_ -= direction_vec_ * movement_speed_;

    if (Input::instance()->keyIsPressed(GLFW_KEY_D))
      position_vec_ += glm::cross(direction_vec_, up_vec_) * movement_speed_;

    if (Input::instance()->keyIsPressed(GLFW_KEY_A))
      position_vec_ -= glm::cross(direction_vec_, up_vec_) * movement_speed_;
  }

  void Camera::updateOrientation()
  {
    // update mouse cursor position
    double x = 0, y = 0;
    Input::instance()->getMousePositionDelta(x, y);
    x *= 0.08; // TODO: change from magic number
    y *= 0.08;

    // yaw
    if (x < -max_yaw_angle_)     x = -max_yaw_angle_;
    else if (x > max_yaw_angle_) x = max_yaw_angle_;

    // put bounds on the yaw for a more natural fps camera feeling
    if (((pitch_angle_ >  90) && (pitch_angle_ <  270)) ||
        ((pitch_angle_ < -90) && (pitch_angle_ > -270)))
      yaw_angle_ -= x;
    else
      yaw_angle_ += x;

    if (yaw_angle_ > 360.0f)
      yaw_angle_ -= 360.0f;
    else if (yaw_angle_ < -360.0f)
      yaw_angle_ += 360.0f;

    // pitch
    if (y < -max_pitch_angle_)
      y = -max_pitch_angle_;
    else if (y > max_pitch_angle_)
      y = max_pitch_angle_;

    pitch_angle_ += y;

    if (pitch_angle_ > 360.0f)
      pitch_angle_ -= 360.0f;
    else if (pitch_angle_ < -360.0f)
      pitch_angle_ += 360.0f;
  }

  void Camera::getViewMat(glm::mat4 &V)
  {
    V = view_mat_;
  }

  void Camera::getProjectionMat(glm::mat4 &P)
  {
    P = projection_mat_;
  }

  void Camera::getMVPMat(glm::mat4 &MVP)
  {
    MVP = model_view_projection_mat_;
  }
} // namespace vv