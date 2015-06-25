
// Written by: Roman Larionov

#ifndef VV_APPLICATION_H
#define VV_APPLICATION_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Renderer.h"

namespace vv
{
namespace app
{
    class App
    {
        public:
            App();
            ~App();

            bool init();
            void run();

        private:
            // OpenGL members.
            GLuint program;
            GLFWwindow* window;

            // Misc members.
            double tick;
            bool running;

            vv::app::Renderer* renderer;
    };
}
}

#endif