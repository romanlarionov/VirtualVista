
#ifndef VIRTUALVISTA_UTILITIES_H
#define VIRTUALVISTA_UTILITIES_H

#include "../deps/glfw/include/GLFW/glfw3.h"

namespace vv
{
    class Utils
    {
    public:
        static GLFWwindow* initWindow();
        static bool createProgram(GLchar const * const vertexSource,
                                  GLchar const * const fragmentSource,
                                  GLuint &program);
        static bool loadShader(std::string filename, GLchar*& shaderSource);
        static GLuint initBuffer(const GLvoid* data);
    };
}

#endif // VIRTUALVISTA_UTILITIES_H
