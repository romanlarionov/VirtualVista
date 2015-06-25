
#include <iostream>
#include <fstream>
#include "Shader.h"

namespace vv
{
namespace vis
{
    vv::vis::Shader::Shader(std::string vert_filename, std::string frag_filename)
    {
        v_name = vert_filename;
        f_name = frag_filename;
        program_id = glCreateProgram();
    }

    vv::vis::Shader::~Shader()
    {
        glDeleteProgram(program_id);
    }

    bool vv::vis::Shader::init()
    {
        return createProgram(v_name, f_name);
    }

    bool vv::vis::Shader::createProgram(std::string vert_filename, std::string frag_filename)
    {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        std::string vert1 = loadShader(vert_filename);
        std::string frag1 = loadShader(frag_filename);

        const GLchar *vert_source = vert1.c_str();
        const GLchar *frag_source = frag1.c_str();

        glShaderSource(vertexShader, 1, &vert_source, NULL);
        glShaderSource(fragmentShader, 1, &frag_source, NULL);

        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);

        auto compilationSuccess = [](GLuint shader) -> bool
        {
            int infoLogLength = 0;
            GLint compileSuccess = GL_FALSE;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);

            if (!compileSuccess)
            {
                char buffer[infoLogLength + 1];
                glGetShaderInfoLog(shader, infoLogLength, NULL, buffer);
                std::cerr << "Error: failed to compile shader.\n" << buffer << "\n";
                glDeleteShader(shader);
                return false;
            }
            return true;
        };

        if (!compilationSuccess(vertexShader) || !compilationSuccess(fragmentShader))
        {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            return false;
        }

        glAttachShader(program_id, vertexShader);
        glAttachShader(program_id, fragmentShader);

        glLinkProgram(program_id);

        GLint linkSuccess = GL_FALSE;
        int programInfoLogLength = 0;

        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &programInfoLogLength);
        glGetProgramiv(program_id, GL_LINK_STATUS, &linkSuccess);

        if (!linkSuccess)
        {
            char buffer[programInfoLogLength + 1];
            glGetProgramInfoLog(program_id, programInfoLogLength, NULL, buffer);
            std::cerr << "Error: program failed to link correctly.\n\n" << buffer << "\n";
            glDeleteProgram(program_id);
            return false;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return true;
    }

    std::string vv::vis::Shader::loadShader(const std::string filename)
    {
        std::ifstream file;
        file.open(filename);
        std::string temp, output;

        if (!file.is_open())
        {
            std::cerr << "ERROR: file - " << filename << " cannot be found." << std::endl;
            return "";
        }

        while (std::getline(file, temp))
            output += temp + "\n";

        if (output.empty())
        {
            std::cerr << "ERROR: file - " << filename << " is empty." << std::endl;
            return "";
        }

        file.close();
        return output;
    }
}
}