

#include <GLFW/glfw3.h>

#include "vv/Time.h"
#include "vv/VirtualVista.h"

namespace vv
{
  /////////////////////////////////////////////////////////////////////// public
  double Time::delta_time_ = 0;
  size_t Time::frame_num_ = 0;
  int Time::frame_rate_ = 0;

  double Time::current()
  {
    return glfwGetTime() * MILLISECOND;
  }


  double Time::delta()
  {
    return delta_time_;
  }


  size_t Time::frameCount()
  {
    return frame_num_;
  }


  int Time::frameRate()
  {
    return frame_rate_;
  }
}