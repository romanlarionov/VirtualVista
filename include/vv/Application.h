
#ifndef VIRTUALVVISTA_APP_H
#define VIRTUALVVISTA_APP_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"

namespace vv
{
  class App
  {
  public:
    App();

    bool init();
    void run();

    GLFWwindow* getWindow();

  private:
    bool first_run_;
    bool first_input_;
    bool app_init_;
    double global_time_;
    double last_x_;
    double last_y_;
    GLFWwindow* window_;

    void handleInput(Camera* cam, double delta_time);
  };
}

#endif // VIRTUALVVISTA_APP_H