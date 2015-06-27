
// Written by: Roman Larionov

#include <iostream>

#include "Application.h"
#include "Shader.h"

namespace vv
{
    App::App()
    {
    }

    App::~App()
    {
    }

    bool App::init()
    {
        glewExperimental = GL_TRUE;
        if (!glfwInit())
        {
            std::cerr << "ERROR: GLFW failed to initialize.\n";
            return EXIT_FAILURE;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed

        if (!window)
        {
            std::cerr << "ERROR: Window context failed to initialize.\n";
            return EXIT_FAILURE; // Maybe have a try catch here
        }

        glfwMakeContextCurrent(window);

        // Needs to be called after window creation else seg fault.
        glewInit();

        return true;
    }

    void App::run()
    {
        // create program
        std::string vert_path = "../src/shaders/vertex.glsl";
        std::string frag_path = "../src/shaders/fragment.glsl";
        Shader shader(vert_path, frag_path);

        std::string vert_path2 = "../src/shaders/vertex2.glsl";
        std::string frag_path2 = "../src/shaders/fragment2.glsl";
        Shader shader2(vert_path2, frag_path2);

        GLfloat vertices[] =
        {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };

        GLfloat vertices2[] =
        {
            -1.0f, -0.5f, 0.0f,
            0.0f, -0.5f, 0.0f,
            -0.5f,  0.0f, 0.0f,
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
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0); // prevent any accidental mis-configurations

        GLuint VAO2 = 0;
        glGenVertexArrays(1, &VAO2);
        glBindVertexArray(VAO2); // from here on, all configurations pertain to this VAO.

        // think of this like a data structure on the device, we're generating a new storage space for our data
        // that we want draw, and then shipping the data from the host to the device.
        GLuint VBO2 = 0;
        glGenBuffers(1, &VBO2);
        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

        // inform the GPU how to understand and process the incoming data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0); // prevent any accidental mis-configurations

        while (!glfwWindowShouldClose(window))
        {
            // If you press the escape key, close the application.
            glfwPollEvents();
            if (glfwGetKey(window, GLFW_KEY_ESCAPE))
                glfwSetWindowShouldClose(window, GL_TRUE);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.useProgram();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);

            shader2.useProgram();
            glBindVertexArray(VAO2);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);

            glfwSwapBuffers(window);
        }

        glDeleteVertexArrays(1, &VAO2);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO2);
        glDeleteBuffers(1, &VBO);
        glfwTerminate();
    }
}