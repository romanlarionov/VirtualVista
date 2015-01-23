
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
        delete renderer;
    }

    bool App::init()
    {
        glewExperimental = GL_TRUE;

        if (!glfwInit())
        {
            std::cerr << "ERROR: GLFW failed to initialize.\n";
            return false;
        }

        window = vv::utils::Utils::initWindow();

        // Needs to be called after window creation else seg fault.
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

        program = glCreateProgram();
        bool programSuccess = vv::utils::Utils::createProgram(vertexShaderSource, fragmentShaderSource, program);

	    if (!programSuccess)
		    return false;

        renderer = new vv::app::Renderer(program);
        renderer->init();

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

            //renderer->render();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
    }
}
}