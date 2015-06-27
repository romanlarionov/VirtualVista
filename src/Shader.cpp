
#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.h"

namespace vv
{
    vv::Shader::Shader(std::string vert_filename, std::string frag_filename)
    {
        program_id = glCreateProgram();

        std::string vert_source = loadShader(vert_filename);
        std::string frag_source = loadShader(frag_filename);
        createProgram(vert_source, frag_source);
    }

    vv::Shader::~Shader()
    {
        glDeleteProgram(program_id);
    }

    bool vv::Shader::createProgram(std::string vert_source, std::string frag_source)
    {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const GLchar *v_source = vert_source.c_str();
        glShaderSource(vertexShader, 1, &v_source, NULL);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar *f_source = frag_source.c_str();
        glShaderSource(fragmentShader, 1, &f_source, NULL);
        glCompileShader(fragmentShader);

        auto compilationSuccess = [](GLuint shader, std::string type) -> bool
        {
            int infoLogLength = 0;
            GLint compileSuccess = GL_FALSE;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);

            if (!compileSuccess)
            {
                char buffer[infoLogLength + 1];
                glGetShaderInfoLog(shader, infoLogLength, NULL, buffer);
                std::cerr << "ERROR: failed to compile " << type << " shader:\n" << buffer << "\n";
                glDeleteShader(shader);
                return false;
            }
            return true;
        };

        bool vert_success = compilationSuccess(vertexShader, "vertex");
        bool frag_success = compilationSuccess(fragmentShader, "fragment");

        if (!vert_success || !frag_success)
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

    std::string vv::Shader::loadShader(const std::string filename)
    {
        std::ifstream file(filename);
        std::string shader_source;

        try
        {
            std::stringstream shader_stream;
            shader_stream << file.rdbuf();
            file.close();

            shader_source = shader_stream.str();
        }
        catch (std::exception e)
        {
            std::cerr << "ERROR: file: " << filename << " not successfully read:\n";
            exit(EXIT_FAILURE);
        }

        return shader_source;
    }
}