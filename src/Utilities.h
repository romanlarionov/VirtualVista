
#include <OpenGL/OpenGL.h>
#include <GLFW/glfw3.h>

namespace vv
{
namespace utils
{
    class Utils
    {
        public:
            static GLFWwindow* initWindow();
            static bool createProgram(GLchar* vertexSource, GLchar* fragmentSource, GLuint &program);
            static bool loadShader(std::string filename, GLchar* shaderSource);
    };
}
}