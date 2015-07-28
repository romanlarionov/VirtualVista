
#ifndef VIRTUALVISTA_APPMANAGER_H
#define VIRTUALVISTA_APPMANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application.h"

namespace vv
{
  class AppManager
  {
  public:
    static bool init();
    static App* instance();

  private:
    static App *app_singleton_;

    AppManager();
    AppManager(AppManager const&) {};
    App& operator=(AppManager const&) const { return *app_singleton_; };

    static void keyboardCallback(GLFWwindow *window, int key, int scan_code, int action, int mods);
    static void mouseCallback(GLFWwindow *window, double curr_x, double curr_y);
  };
}

#endif // VIRTUALVISTA_APPMANAGER_H