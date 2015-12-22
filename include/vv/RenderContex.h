
#ifndef VIRTUALVISTA_RENDERCONTEX_H
#define VIRTUALVISTA_RENDERCONTEX_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace vv
{
  class RenderContex
  {
  public:
    RenderContex();
    ~RenderContex();

    bool initializeContext(int x, int y, int width, int height);
    GLFWwindow* getWindow();

  private:
    GLFWwindow *window_;

  };
}

#endif // VIRTUALVISTA_RENDERCONTEX_H