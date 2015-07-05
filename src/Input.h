
#ifndef VIRTUALVISTA_INPUT_H
#define VIRTUALVISTA_INPUT_H

#include <vector>
#include <GLFW/glfw3.h>

namespace vv
{
  class Input
  {
    friend class AppManager;

  public:
    static Input* instance();

    bool keyIsPressed(int key);
    void getMouseValues(double &x, double &y);
    void getMousePositionDelta(double &x, double &y);

  private:
    static Input *input_singleton_;
    double last_x_;  // previous cursor coordinates
    double last_y_;
    double curr_x_;
    double curr_y_;
    std::vector<bool> key_pressed_tracker_;

    Input();
    Input(Input const&) {};
    Input& operator=(Input const&) const { return *input_singleton_; };

    // only used in one place, don't need to be seen by anything other than AppManager
    void keyboardEventsCallback(GLFWwindow* window, int key, int scan_code, int action, int mods);
    void mouseEventsCallback(GLFWwindow *window, double curr_x, double curr_y);
  };
}

#endif // VIRTUALVISTA_INPUT_H