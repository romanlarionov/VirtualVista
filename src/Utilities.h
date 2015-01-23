
#ifndef VV_UTILITIES_H
#define VV_UTILITIES_H

#include <GLFW/glfw3.h>

namespace vv
{
namespace utils
{
    class Utils
    {
        public:
            static GLFWwindow* initWindow();
            static bool createProgram(GLchar const * const vertexSource,
                                      GLchar const * const fragmentSource,
                                      GLuint &program);
            static bool loadShader(std::string filename, GLchar* shaderSource);
	        static GLuint initBuffer(const GLvoid* data);
    };
}
}

#endif