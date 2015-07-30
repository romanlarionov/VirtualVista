
#define GLFW_INCLUDE_GLCOREARB

#ifdef __APPLE__
# define __gl3_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#include "AppManager.h"

using namespace vv;

int main(int argc, char* argv[])
{
  // TODO: process command line input

  if (!AppManager::init()) return EXIT_FAILURE;
  AppManager::instance()->run();

  return EXIT_SUCCESS;
}