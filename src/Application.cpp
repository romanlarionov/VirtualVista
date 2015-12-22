
#include <iostream>

#include "vv/Application.h"

namespace vv
{
  /////////////////////////////////////////////////////////////////////// public
  Application::Application() :
    application_initialized_(false)
  {
    contex_ = new RenderContex;
    input_manager_ = new InputManager;
  }


  Application::~Application()
  {
    delete contex_;
    delete input_manager_;
  }


  bool Application::init()
  {
    if (!application_initialized_)
    {
      input_manager_->setEventHandling();

      bool contex_success = contex_->initializeContext(0, 0, 640, 480);
      if (!contex_success) return false;

      glfwSetKeyCallback(contex_->getWindow(), GLFWState::dispatchKeyCallback);
      glfwSetCursorPosCallback(contex_->getWindow(), GLFWState::dispatchMouseCallback);

      application_initialized_ = true;
    }

    return true;
  }


  void Application::run()
  {
    while (!glfwWindowShouldClose(contex_->getWindow()))
    {
      glfwPollEvents();
      if (input_manager_->keyIsPressed(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(contex_->getWindow(), GL_TRUE);

      glfwSwapBuffers(contex_->getWindow());
    }

    // clean up
    glfwDestroyWindow(contex_->getWindow());
    glfwTerminate();
  }
  ////////////////////////////////////////////////////////////////////// private

} // namespace vv
