
// Written by: Roman Larionov

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Scene.h"

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

            vv::scene::Scene* scene;
    };
}
}