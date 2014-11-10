
#include <iostream>
#include <fstream>
#include "Utilities.h"

namespace vv
{
namespace utils
{
    bool Utils::createProgram(GLchar* vertexSource, GLchar* fragmentSource, GLuint &program)
    {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
        glCompileShader(fragmentShader);

        auto checkCompileStatus = [](GLuint shader)
        {
            int infoLogLength = 0;
            GLint compileSuccess = GL_FALSE;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);

            if (!compileSuccess)
            {
                char buffer[infoLogLength + 1];
                glGetShaderInfoLog(shader, infoLogLength, NULL, buffer);
                std::cerr << "Error: failed to compile shader. " << compileSuccess << std::endl << buffer << std::endl;
                glDeleteShader(shader);
                return false;
            }
            return true;
        };

        if (!checkCompileStatus(vertexShader) || !checkCompileStatus(fragmentShader))
        {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            return false;
        }

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glBindAttribLocation(program, 0, "position");
        glLinkProgram(program);

        GLint linkSuccess = GL_FALSE;
        int programInfoLogLength = 0;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &programInfoLogLength);
        glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);

        if (!linkSuccess)
        {
            char buffer[programInfoLogLength + 1];
            glGetProgramInfoLog(program, programInfoLogLength, NULL, buffer);
            std::cerr << "Error: program failed to link correctly.\n\n" << buffer << std::endl;
            glDeleteProgram(program);
            return false;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return true;
    }

    GLFWwindow* Utils::initWindow()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed

        if (!window)
        {
            std::cerr << "ERROR: window creation failed." << std::endl;
            exit(EXIT_FAILURE);
        }

        // This makes the window active.
        glfwMakeContextCurrent(window);

        return window;
    }

    bool Utils::loadShader(std::string filename, GLchar* shaderSource)
    {
        std::ifstream file;
        file.open(filename);

        if (!file.is_open())
        {
            std::cerr << "ERROR: file - " << filename << " cannot be found." << std::endl;
            return false;
        }

        std::string temp;
        std::string finished;

        while (!file.eof())
        {
            std::getline(file, temp);
            finished += temp + "\n";
        }

        if (finished.empty())
        {
           std::cerr << "ERROR: file - " << filename << " is empty." << std::endl;
           return false;
        }

        int i;
        unsigned long length = finished.length();
        for (i = 0; i < length; i++)
            shaderSource[i] = finished[i];

        shaderSource[i] = '\0'; // NULL character at the end of c strings.

        file.close();
        return true;
    }
}
}