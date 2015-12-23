
#include <iostream>

#include "vv/Application.h"
#include "vv/Time.h"
#include "vv/VirtualVista.h"

namespace vv
{
  /////////////////////////////////////////////////////////////////////// public
  Application::Application(int argc, char **argv) :
    first_run_(true),
    initialized_(false),
    quit_(false)
  {
    contex_ = new RenderContex;
    input_manager_ = new InputManager;
    resource_manager_ = new ResourceManager;
  }


  Application::~Application()
  {
    SAFE_DELETE(contex_);
    SAFE_DELETE(input_manager_);
    SAFE_DELETE(resource_manager_);
  }


  bool Application::init()
  {
    if (!initialized_)
    {
      input_manager_->setEventHandling();
      if (!contex_->init(0, 0, 640, 480)) return false;

      glfwSetKeyCallback(contex_->getWindow(), GLFWState::dispatchKeyCallback);
      glfwSetCursorPosCallback(contex_->getWindow(), GLFWState::dispatchMouseCallback);

      initialized_ = true;
    }

    return true;
  }


  void Application::run()
  {
    resource_manager_->addShader("../src/shaders/", "light_cube"); // delete!!!


    const double UPDATE_STEP = 2000; // todo: move somewhere else
    double total_update_time = 0, previous_time = 0, fps_time_stamp = 0;
    int frame_counter = 0; // stores number of frames every second

    while (!quit_)
    {
      // timing calculations
      double current_time = Time::current();
      if (first_run_)
      {
        fps_time_stamp = current_time;
        previous_time = current_time;
        first_run_ = false;
      }

      Time::delta_time_ = current_time - previous_time;
      previous_time = current_time;
      total_update_time += Time::delta_time_;

      // update frames per second calculation
      Time::frame_num_++;
      frame_counter++;
      if (((current_time - fps_time_stamp) > 250.0) && (frame_counter > 10))
      {
        Time::frame_rate_ = (int)(MILLISECOND * frame_counter / (current_time - fps_time_stamp));
        fps_time_stamp = current_time;
        frame_counter = 0;
        //std::cout << "Frame rate: " << Time::frame_rate_ << "\n";
      }

      // update scene as many times as possible within the alloted time
      while (total_update_time >= UPDATE_STEP)
      {
        // update function
        total_update_time -= UPDATE_STEP;
      }

      // render
      glfwPollEvents();
      glfwSwapBuffers(contex_->getWindow());

      if (input_manager_->keyIsPressed(GLFW_KEY_ESCAPE)) quit_ = true;

    }
  }


  void Application::shutdown()
  {
    glfwSetWindowShouldClose(contex_->getWindow(), GL_TRUE);
    glfwDestroyWindow(contex_->getWindow());
    glfwTerminate();
  }
  ////////////////////////////////////////////////////////////////////// private

} // namespace vv
