
#ifndef VIRTUALVISTA_APPLICATION_H
#define VIRTUALVISTA_APPLICATION_H

#include <vector>

#include <glad/glad.h>

#include "RenderContex.h"
#include "InputManager.h"
#include "ResourceManager.h"

namespace vv
{
  class Application
  {
  public:
    Application();
    ~Application();

    bool init();
    void run();

  private:
    bool initialized_;

    RenderContex *contex_;
    InputManager *input_manager_;
    ResourceManager *resource_manager_;
    
  };
}

#endif // VIRTUALVISTA_APPLICATION_H