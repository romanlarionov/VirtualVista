
/*
    Written By: Roman Larionov

    Description: Test OpenGL Program for me to practice writing
    computer graphics in C++

    This Program depends on the GLFW OpenGL Input/Window Management library.
    It also needs GLM, which is an OpenGL linear algebra library.
 */

#include <iostream>
#include "AppManager.h"

using namespace vv;

int main(int argc, char* argv[])
{
  // TODO: process command line input

  if (!AppManager::init()) return EXIT_FAILURE;
  AppManager::instance()->run();
  return EXIT_SUCCESS;
}