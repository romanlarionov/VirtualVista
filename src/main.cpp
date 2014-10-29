
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
#include <vector>
#include <fstream>
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

// Function Prototypes.
GLFWwindow* initWindow();
void loadShader(std::string filename, GLchar* shaderSource);

int main()
{
    // If the program hasn't loaded properly.
    if (!glfwInit())
        exit(EXIT_FAILURE);

    GLFWwindow* window = initWindow();

    glewExperimental = GL_TRUE;
    glewInit();

    // Scan in Shader code from files.
    // TODO: change from magic number.
    GLchar vertexShaderSource[1000];
    GLchar fragmentShaderSource[1000];

    loadShader("../src/shaders/shader.vert", vertexShaderSource);
    loadShader("../src/shaders/shader.frag", fragmentShaderSource);

    if (!vertexShaderSource || !fragmentShaderSource)
        std::cerr << "ERROR: vertex or fragment shader code not scanning in correctly." << std::endl;

    // Main Event Loop.
    while (!glfwWindowShouldClose(window))
    {
        // If you press the escape key, close the application.
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, GL_TRUE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

GLFWwindow* initWindow()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed

    // This makes the window active.
    glfwMakeContextCurrent(window);

    return window;
}

void loadShader(std::string filename, GLchar* shaderSource)
{
    std::ifstream file;
    file.open(filename);

    if (!file.is_open())
    {
        std::cerr << "ERROR: file - " << filename << " cannot be found." << std::endl;
        exit(-1);
    }

    std::string temp;
    std::string finished;

    while (!file.eof())
    {
        std::getline(file, temp);
        finished += temp;
    }

    if (finished.empty())
    {
       std::cerr << "ERROR: file - " << filename << " is empty." << std::endl;
       exit(-2);
    }

    int length = finished.length(), i;
    for (i = 0; i < length; i++)
        shaderSource[i] = finished[i];

    shaderSource[i] = '\0'; // NULL character at the end of c strings.

    file.close();
}







