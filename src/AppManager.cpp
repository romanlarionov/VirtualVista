
#include <iostream>

#include "AppManager.h"
#include "Settings.h"
#include "Input.h"

namespace vv
{
  App* AppManager::app_singleton_ = NULL;

  bool AppManager::init()
  {
    if (!app_singleton_)
    {
      app_singleton_ = new App;
      if (!app_singleton_->init())
      {
        delete app_singleton_;
        return false;
      }
    }

    glfwSetKeyCallback(app_singleton_->getWindow(), keyboardCallback);
    glfwSetCursorPosCallback(app_singleton_->getWindow(), mouseCallback);
    glfwSetFramebufferSizeCallback(app_singleton_->getWindow(), framebufferSizeCallback);
    return true;
  }


  App* AppManager::instance()
  {
    if (!app_singleton_)
    {
      std::cerr << "ERROR: failed to access instance of Application.\n";
      std::cerr << "Probably forgot AppManager::init() somewhere.\n";
      exit(EXIT_FAILURE);
    }

    return app_singleton_;
  }


  void AppManager::keyboardCallback(GLFWwindow *window, int key, int scan_code, int action, int mods)
  {
    Input::instance()->keyboardEventsCallback(window, key, scan_code, action, mods);
  }


  void AppManager::mouseCallback(GLFWwindow *window, double curr_x, double curr_y)
  {
    Input::instance()->mouseEventsCallback(window, curr_x, curr_y);
  }


  void AppManager::framebufferSizeCallback(GLFWwindow* window, int width, int height)
  {
    glViewport(0, 0, width, height);
    Settings::instance()->setViewport(0, 0, width, height);
  }
} // namespace vv