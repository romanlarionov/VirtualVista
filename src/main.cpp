
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
#include <OpenGL/OpenGL.h>


int main(int argc, char* argv[])
{
    /*vv::app::App virtualVistaApp;

    if (!virtualVistaApp.init())
        return EXIT_FAILURE;

    virtualVistaApp.run();*/

    GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    //GLuint VBO;
    //glGenBuffers(1, &VBO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //GLchar *frag_source, *vert_source;
    //vv::Utils::loadShader("../src/shaders/fragment.glsl", frag_source);
    //vv::Utils::loadShader("../src/shaders/vertex.glsl", vert_source);



    return EXIT_SUCCESS;
}


