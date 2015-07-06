
#ifndef VIRTUALVISTA_SETTINGS_H
#define VIRTUALVISTA_SETTINGS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

enum camera_type
{
  ORTHOGONAL  = 0,
  PERSPECTIVE = 1
};

namespace vv
{
  class Settings
  {
  public:
    static Settings* instance();

    void setDefault();

    void setViewport(const int start_x,
                     const int start_y,
                     const int width,
                     const int height);

    void setFieldOfView(const float fov);
    void setClipDistance(const float near, const float far);

    std::string getShaderLocation() const;
    bool getWindowsShouldResize() const;
    float getCameraType() const;
    void getViewport(int &x, int &y, int &width, int &height) const;
    void getPerspective(float &fov, float &aspect, float &near, float &far) const;
    double getMovementSpeed() const;
    double getRotationSpeed() const;


  private:
    static Settings* instance_;

    bool default_;

    bool window_resize_;
    bool camera_type_;

    // Viewport
    int start_x_;
    int start_y_;
    int window_width_;
    int window_height_;

    // Perspective settings
    float field_of_view_;
    float aspect_ratio_;
    float near_clip_;
    float far_clip_;

    std::string shader_location_;

    // Speed
    double movement_speed_;
    double rotation_speed_;

    Settings();
    Settings(const Settings& s);
    Settings* operator=(const Settings& s) const;
  };
}

#endif // VIRTUALVISTA_SETTINGS_H