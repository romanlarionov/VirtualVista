
/*
    Written By: Roman Larionov

    Description: Test OpenGL Program for me to practice writing
    computer graphics in C++

    This Program depends on the GLFW OpenGL Input/Window Management library.
    It also needs GLM, which is an OpenGL linear algebra library.
 */

// This is a GLFW built in macro. It tells it to include gl3.h instead of gl.h.
#define GLFW_INCLUDE_GLCOREARB

#ifdef __APPLE__
# define __gl3_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#include <iostream>
#include "Application.h"

int main(int argc, char* argv[])
{
    vv::app::App virtualVistaApp;

    if (!virtualVistaApp.initGL())
        return EXIT_FAILURE;

    virtualVistaApp.run();

    glfwTerminate();
    return EXIT_SUCCESS;
}


