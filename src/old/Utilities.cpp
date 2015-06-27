
#include "Utilities.h"

namespace vv
{
    bool Utils::initWindow(GLFWwindow*& window)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed

        if (!window) return false;
        glfwMakeContextCurrent(window);
        return true;
    }
}