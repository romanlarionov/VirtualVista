
#include <iostream>

#include "vv/Application.h"

namespace vv
{
  /////////////////////////////////////////////////////////////////////// public
  Application::Application() :
    initialized_(false)
  {
    contex_ = new RenderContex;
    input_manager_ = new InputManager;
    resource_manager_ = new ResourceManager;
  }


  Application::~Application()
  {
    delete contex_;
    delete input_manager_;
    delete resource_manager_;
  }


  bool Application::init()
  {
    if (!initialized_)
    {
      input_manager_->setEventHandling();

      bool contex_success = contex_->initializeContext(0, 0, 640, 480);
      if (!contex_success) return false;

      glfwSetKeyCallback(contex_->getWindow(), GLFWState::dispatchKeyCallback);
      glfwSetCursorPosCallback(contex_->getWindow(), GLFWState::dispatchMouseCallback);

      initialized_ = true;
    }

    return true;
  }


  void Application::run()
  {
    resource_manager_->addShader("../src/shaders/", "light_cube"); // delete!!!

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
