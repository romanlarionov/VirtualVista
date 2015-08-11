
#include "vv/Settings.h"

namespace vv
{
  Settings* Settings::instance_ = nullptr;

  /////////////////////////////////////////////////////////////////////// public
  Settings* Settings::instance()
  {
    if (!instance_)
      instance_ = new Settings;
    return instance_;
  }


  void Settings::setDefault()
  {
    // window settings
    window_resize_ = false;

    // viewport
    start_x_ = 0;
    start_y_ = 0;
    window_width_ = 800;
    window_height_ = 600;
    aspect_ratio_ = 800 / 600;
    camera_type_ = PERSPECTIVE;

    // fov
    field_of_view_ = 45.0f;

    // clipping
    near_clip_ = 0.1f;
    far_clip_ = 1000.0f;

    shader_location_ = "../src/shaders/";
    assets_location_ = "../assets/";

    // speed
    movement_speed_ = 4.0;
    rotation_speed_ = 0.35; // TODO: check if good initial values

    default_ = true;
  }


  void Settings::setViewport(const int start_x, const int start_y, const int width, const int height)
  {
    start_x_ = start_x;
    start_y_ = start_y;
    window_width_ = width;
    window_height_ = height;
    aspect_ratio_ = width / height;
    default_ = false;
  }


  void Settings::setFieldOfView(const float fov)
  {
    field_of_view_ = fov;
    default_ = false;
  }


  void Settings::setClipDistance(const float near, const float far)
  {
    near_clip_ = near;
    far_clip_ = far;
    default_ = false;
  }


  std::string Settings::getShaderLocation() const
  {
    return shader_location_;
  }


  std::string Settings::getAssetsLocation() const
  {
    return assets_location_;
  }


  float Settings::getCameraType() const
  {
    return camera_type_;
  }


  void Settings::getViewport(int &x, int &y, int &width, int &height) const
  {
    x = start_x_;
    y = start_y_;
    width = window_width_;
    height = window_height_;
  }


  void Settings::getPerspective(float &fov, float &aspect, float &near, float &far) const
  {
    fov = field_of_view_;
    aspect = aspect_ratio_;
    near = near_clip_;
    far = far_clip_;
  }


  double Settings::getMovementSpeed() const
  {
    return movement_speed_;
  }


  double Settings::getRotationSpeed() const
  {
    return rotation_speed_;
  }


  ////////////////////////////////////////////////////////////////////// private
  Settings::Settings()
  {
    setDefault();
  }
} // namespace vv