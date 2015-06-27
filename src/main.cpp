
/*
    Written By: Roman Larionov

    Description: Test OpenGL Program for me to practice writing
    computer graphics in C++

    This Program depends on the GLFW OpenGL Input/Window Management library.
    It also needs GLM, which is an OpenGL linear algebra library.
 */


#include <iostream>
#include "Application.h"
using namespace vv;

int main(int argc, char* argv[])
{
    App app;

    if (!app.init()) return EXIT_FAILURE;

    app.run();

    return EXIT_SUCCESS;
}