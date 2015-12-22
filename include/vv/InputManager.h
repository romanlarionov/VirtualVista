
#ifndef VIRTUALVISTA_INPUTMANAGER_H
#define VIRTUALVISTA_INPUTMANAGER_H

#include <vector>

#include "GLFWState.h"

namespace vv
{
  class InputManager : public GLFWState
  {
  public:
    InputManager();

    bool keyIsPressed(int key);
    void getMouseValues(double& x, double& y);

  private:
    double curr_x_;
    double curr_y_;
    std::vector<bool> key_pressed_tracker_;

    void keyCallback(GLFWwindow *window, int key, int scan_code, int action, int mods);
    void mouseCallback(GLFWwindow *window, double curr_x, double curr_y);

  };
}

#endif // VIRTUALVISTA_INPUTMANAGER_H