
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

#include <vector>
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

// Function Prototypes.
GLFWwindow* initWindow();
GLuint createProgram(GLchar const* vertexSource, GLchar const* fragmentSource);

int main()
{
    // If the program hasn't loaded properly.
    if (!glfwInit())
        exit(EXIT_FAILURE);

    GLFWwindow* window = initWindow();

    glewExperimental = GL_TRUE;
    glewInit();

    int numVerticies = 3;

    float verticies[] = {
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

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

GLuint createProgram(GLchar const* vertexSource, GLchar const* fragmentSource)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    auto shaderCompiled = [] (GLuint shader) -> bool
    {
        GLint *compileSuccess = NULL;
        glGetShaderiv(shader, GL_COMPILE_STATUS, compileSuccess);

        if (!compileSuccess)
        {
            printf("Error: failed to compile shader.\n");
            glDeleteShader(shader);
            return false;
        }

        return true;
    };

    if (!shaderCompiled(vertexShader) || !shaderCompiled(fragmentShader))
        return 0;

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint *linkSuccess = NULL;
    glGetProgramiv(program, GL_LINK_STATUS, linkSuccess);

    if (!linkSuccess)
    {
        printf("Error: program failed to link correctly.\n");
        glDeleteProgram(program);
        return 0;
    }

    return program;
}


