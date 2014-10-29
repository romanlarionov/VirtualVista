
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
GLuint createProgram(GLchar* vertexSource, GLchar* fragmentSource);

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

    GLuint program = createProgram(vertexShaderSource, fragmentShaderSource);

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

GLuint createProgram(GLchar* vertexSource, GLchar* fragmentSource)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    auto shaderCompiled = [] (GLuint shader)
    {
        GLint compileSuccess;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);

        if (!compileSuccess)
        {
            char buffer[512];
            glGetShaderInfoLog(shader, 512, NULL, buffer);
            std::cerr << "Error: failed to compile shader. " << compileSuccess << "\n" << buffer << std::endl;
            glDeleteShader(shader);
            exit(EXIT_FAILURE);
        }
    };

    shaderCompiled(vertexShader);
    shaderCompiled(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glBindAttribLocation(program, 0, "position");
    glLinkProgram(program);

    GLint linkSuccess;
    glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);

    if (!linkSuccess)
    {
        std::cerr << "Error: program failed to link correctly." << std::endl;
        glDeleteProgram(program);
        exit(EXIT_FAILURE);
    }

    glUseProgram(program);

    return program;
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
        finished += temp + "\n";
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







