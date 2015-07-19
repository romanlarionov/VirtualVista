
#include <iostream>

#include "Input.h"

namespace vv
{
  Input* Input::input_singleton_ = NULL;

  Input::Input() :
    curr_x_(0),
    curr_y_(0)
  {
    key_pressed_tracker_.resize(GLFW_KEY_LAST);
  }


  Input* Input::instance()
  {
    if (!input_singleton_)
      input_singleton_ = new Input;
    return input_singleton_;
  }


  bool Input::keyIsPressed(int key)
  {
    if ((key >= 0) && (key < GLFW_KEY_LAST))
      return key_pressed_tracker_[key];
    return false;
  }


  void Input::getMouseValues(double& x, double& y)
  {
    x = curr_x_;
    y = curr_y_;
  }


  void Input::keyboardEventsCallback(GLFWwindow *window, int key, int scan_code, int action, int mods)
  {
    if ((key >= 0) && (key < GLFW_KEY_LAST))
    {
      if (action == GLFW_PRESS)
        key_pressed_tracker_[key] = true;
      else if (action == GLFW_RELEASE)
        key_pressed_tracker_[key] = false;
    }
  }


  void Input::mouseEventsCallback(GLFWwindow *window, double curr_x, double curr_y)
  {
    curr_x_ = curr_x;
    curr_y_ = curr_y;
  }
} // namespace vv