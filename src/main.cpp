
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
#include "vector"
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

// Function Prototypes.
GLFWwindow* initWindow();

int main()
{
    // If the program hasn't loaded properly.
    if (!glfwInit())
        exit(EXIT_FAILURE);

    GLFWwindow* window = initWindow();

    glewExperimental = GL_TRUE;
    glewInit();

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


/******************
    Functions.
 ******************/

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


/******************
    Classes.
 ******************/

/*
    SimpleMeshObject: This is an implementation of a very simplistic
    object to be rendered. It stores all of the info on said object
    and controls it's individual drawing every frame.
*/

class SimpleMeshObject
{
    public:

        std::vector<GLuint>* buffers;

        SimpleMeshObject()
        {
            buffers = new std::vector<GLuint>();
        }

        virtual ~SimpleMeshObject()
        {
        }

        void draw()
        {
            //glDrawArrays(GL_TRIANGLES, 0, );
        }
};

/*
    Scene: This stores information on the rendering process and stores a
    draw call to update the scene every frame.
*/

class Scene
{
    public:

        std::vector<SimpleMeshObject>* objects;

        Scene()
        {
            objects = new std::vector<SimpleMeshObject>();
        }

        virtual ~Scene()
        {
        }

        void addObjects(SimpleMeshObject object)
        {
            objects->push_back(object);
        }

        /*
        void draw(auto uniformSetter, auto attributeSetter)
        {
            for (auto currObject = objects->begin(); currObject != objects->end(); currObject++)
                currObject->draw(uniformSetter, attributeSetter);
        }
        */
};









