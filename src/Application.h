
// Written by: Roman Larionov

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "GL/glew.h"

namespace vv
{
namespace app
{
    class App
    {
        public:
            App();
            ~App();

            bool initGL();
            void run();

        private:
            // OpenGL members.
            GLuint program;
            GLFWwindow* window;

            // Misc members.
            double tick;
            bool running;
    };
}
}