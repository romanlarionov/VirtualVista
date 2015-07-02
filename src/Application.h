
#ifndef VIRTUALVVISTA_APP_H
#define VIRTUALVVISTA_APP_H

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace vv
{
  class App
  {
    friend class AppManager;
  public:
    App();

    bool init();
    void run();

  private:
    bool first_run_;
    bool app_init_;
    GLdouble global_time_;
    unsigned int window_width_;
    unsigned int window_height_;
    GLFWwindow* window_;

    void handleInput();
  };
}

#endif // VIRTUALVVISTA_APP_H