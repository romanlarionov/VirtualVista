
#ifndef VIRTUALVISTA_INPUT_H
#define VIRTUALVISTA_INPUT_H

#include <vector>
#include <GLFW/glfw3.h>

namespace vv
{
  class Input
  {
  public:
    static Input* instance();

    bool keyIsPressed(int key);
    void getMouseValues(GLdouble& x, GLdouble& y);

    void keyboardEventsCallback(GLFWwindow* window, int key, int scan_code, int action, int mods);
    void mouseEventsCallback(GLFWwindow *window, double curr_x, double curr_y);

  private:
    static Input *input_singleton_;
    GLdouble last_x_;  // previous cursor coordinates
    GLdouble last_y_;
    std::vector<bool> key_pressed_tracker_;

    Input();
    Input(Input const&) {};
    Input& operator=(Input const&) const { return *input_singleton_; };
  };
}

#endif // VIRTUALVISTA_INPUT_H