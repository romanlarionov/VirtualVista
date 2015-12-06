
#ifndef VIRTUALVISTA_APPMANAGER_H
#define VIRTUALVISTA_APPMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"

namespace vv
{
  class AppManager
  {
  public:
    static App* instance();
    static bool init();

  private:
    static App *app_singleton_;

    AppManager();
    AppManager(AppManager const&);
    App& operator=(AppManager const&);

    static void keyboardCallback(GLFWwindow *window, int key, int scan_code, int action, int mods);
    static void mouseCallback(GLFWwindow *window, double curr_x, double curr_y);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
  };
}

#endif // VIRTUALVISTA_APPMANAGER_H