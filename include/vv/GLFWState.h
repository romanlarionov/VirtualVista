
#ifndef VIRTUALVISTA_GLFWSTATE_H
#define VIRTUALVISTA_GLFWSTATE_H

#include <GLFW/glfw3.h>

namespace vv
{
  class GLFWState
  {
  public:
    virtual void keyCallback(GLFWwindow *window, int key, int scan_code, int action, int mods) = 0;
    virtual void mouseCallback(GLFWwindow *window, double curr_x, double curr_y) = 0;

    static void dispatchKeyCallback(GLFWwindow *window, int key, int scan_code, int action, int mods)
    {
      if (state_instance)
        state_instance->keyCallback(window, key, scan_code, action, mods);
    }

    static void dispatchMouseCallback(GLFWwindow *window, double curr_x, double curr_y)
    {
      if (state_instance)
        state_instance->mouseCallback(window, curr_x, curr_y);
    }

    virtual void setEventHandling()
    {
      state_instance = this;
    }

  private:
    static GLFWState *state_instance;

  };
}

#endif // VIRTUALVISTA_GLFWSTATE_H