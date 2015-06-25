
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
#include <fstream>
#include <vector>

#include <GLFW/glfw3.h>
#include "glew.h"

#include "Shader.h"
#include "Utilities.h"

int main(int argc, char* argv[])
{
    glewExperimental = GL_TRUE;
    if (!glfwInit())
    {
        std::cerr << "ERROR: GLFW failed to initialize.\n";
        return EXIT_FAILURE;
    }

    // initialize context
    GLFWwindow* window;
    if (!vv::Utils::initWindow(window))
    {
        std::cerr << "ERROR: Window context failed to initialize.\n";
        return EXIT_FAILURE; // Maybe have a try catch here
    }

    // Needs to be called after window creation else seg fault.
    glewInit();
    glClearColor(0.0f, 0.0f, 0.2f, 0.0f);   // Slightly blue background.

    // create program
    vv::vis::Shader shader("../src/shaders/fragment.glsl", "../src/shaders/vertex.glsl");
    shader.init();

    GLfloat vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    // create vertex array object that stores a single configuration of drawing specifications like
    // which attributes to use, how many VBOs to use, etc.
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // from here on, all configurations pertain to this VAO.

    // think of this like a data structure on the device, we're generating a new storage space for our data
    // that we want draw, and then shipping the data from the host to the device.
    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // inform the GPU how to understand and process the incoming data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // prevent any accidental mis-configurations

    // draw
    glUseProgram(shader.getProgramId());
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))  {}

    return EXIT_SUCCESS;
}

