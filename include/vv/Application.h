
#ifndef VIRTUALVISTA_APPLICATION_H
#define VIRTUALVISTA_APPLICATION_H

#include <vector>

#include <glad/glad.h>

#include "RenderContex.h"
#include "InputManager.h"

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
    bool application_initialized_;
    RenderContex *contex_;
    InputManager *input_manager_;

    std::vector<bool> key_pressed_tracker_;

  };
}

#endif // VIRTUALVISTA_APPLICATION_H