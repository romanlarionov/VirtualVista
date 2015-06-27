
// Written by: Roman Larionov

#ifndef VIRTUALVVISTA_APPLICATION_H
#define VIRTUALVVISTA_APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace vv
{
    class App
    {
        public:
            App();
            ~App();

            bool init();
            void run();

        private:

            GLFWwindow* window;
    };
}

#endif // VIRTUALVVISTA_APPLICATION_H