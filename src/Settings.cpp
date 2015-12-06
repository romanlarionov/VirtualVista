
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
    aspect_ratio_ = (float)(800.0 / 600.0);
    camera_type_ = PERSPECTIVE;

    // fov
    field_of_view_ = 45.0f;

    // clipping
    near_clip_ = 0.1f;
    far_clip_ = 1000.0f;

    // todo: make sure this works for every platform
#ifdef _WIN32
    shader_location_ = "../../src/shaders/";
    assets_location_ = "../../assets/";
#else
    shader_location_ = "../src/shaders/";
    assets_location_ = "../assets/";
#endif

    // speed
    movement_speed_ = 4.0;
    rotation_speed_ = 0.35; // TODO: check if good initial values

    max_lights_in_scene_ = 16;

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


  void Settings::setClipDistance(float near_plane, float far_plane)
  {
    near_clip_ = near_plane;
    far_clip_ = far_plane;
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


  void Settings::getPerspective(float &fov, float &aspect, float &near_plane, float &far_plane) const
  {
    fov = field_of_view_;
    aspect = aspect_ratio_;
    near_plane = near_clip_;
    far_plane = far_clip_;
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