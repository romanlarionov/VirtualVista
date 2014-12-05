
// Written by: Roman Larionov

#include <iostream>
#include "Application.h"
#include "Utilities.h"
#include "glm/glm.hpp"

namespace vv
{
namespace app
{
    App::App()
    : running (true)
    {
    }

    App::~App()
    {
        glDeleteProgram(program);
    }

    bool App::init()
    {
        glewExperimental = GL_TRUE;

        if (!glfwInit())
        {
            std::cerr << "ERROR: GLFW failed to initialize." << std::endl;
            return false;
        }

        window = vv::utils::Utils::initWindow();
	    renderer = new vv::app::Renderer(program);

        glewInit();
        glClearColor(0.0f, 0.0f, 0.2f, 0.0f);   // Slightly blue background.

        // Scan in Shader code from files.
        // TODO: change from magic number.
        GLchar vertexShaderSource[1000];
        GLchar fragmentShaderSource[1000];

        // Save shader source into variables.
        bool vertexSuccess = vv::utils::Utils::loadShader("../src/shaders/vertex.glsl", vertexShaderSource);
        bool fragSuccess   = vv::utils::Utils::loadShader("../src/shaders/fragment.glsl", fragmentShaderSource);

        if (!vertexSuccess || !fragSuccess)
            return false;

        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        float vertices[] =
        {
            0.0f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
        };

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        program = glCreateProgram();
        bool programSuccess = vv::utils::Utils::createProgram(vertexShaderSource, fragmentShaderSource, program);

	    if (!programSuccess)
		    return false;

        GLint posAttrib = glGetAttribLocation(program, "position");
        glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(posAttrib);

        GLint colorUni = glGetUniformLocation(program, "triangleColor");
        glUniform3f(colorUni, 1.0f, 0.0f, 0.0f);

        return programSuccess;
    }

    void App::run()
    {
        // Main Event Loop.
        while (!glfwWindowShouldClose(window))
        {
            // If you press the escape key, close the application.
            if (glfwGetKey(window, GLFW_KEY_ESCAPE))
                glfwSetWindowShouldClose(window, GL_TRUE);

            glUseProgram(program);

            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
    }
}
}