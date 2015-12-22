
#include <iostream>

#include "vv/RenderContex.h"

namespace vv
{
  /////////////////////////////////////////////////////////////////////// public
  RenderContex::RenderContex()
  {
  }


  RenderContex::~RenderContex()
  {
  }


  bool RenderContex::initializeContext(int x, int y, int width, int height)
  {
    if (!glfwInit())
    {
      std::cerr << "ERROR: GLFW failed to initialize.\n";
      return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window_ = glfwCreateWindow(width, height, "Virtual Vista", nullptr, nullptr);

    glfwMakeContextCurrent(window_);
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!window_)
    {
      std::cerr << "ERROR: Window context failed to initialize.\n";
      glfwTerminate();
      return false;
    }

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
      std::cout << "ERROR: Failed to initialize OpenGL context.\n";
      glfwTerminate();
      return false;
    }

    return true;
  }


  GLFWwindow* RenderContex::getWindow()
  {
    return window_;
  }
} // namespace vv