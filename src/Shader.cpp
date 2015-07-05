
#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.h"

namespace vv
{
  vv::Shader::Shader(std::string vert_filename, std::string frag_filename)
  {
    program_id_ = glCreateProgram();

    std::string vert_source = loadShader(vert_filename);
    std::string frag_source = loadShader(frag_filename);
    createProgram(vert_source, frag_source);
  }

  vv::Shader::~Shader()
  {
    glDeleteProgram(program_id_);
  }

  bool vv::Shader::createProgram(std::string vert_source, std::string frag_source)
  {
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *v_source = vert_source.c_str();
    glShaderSource(vertex_shader, 1, &v_source, NULL);
    glCompileShader(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *f_source = frag_source.c_str();
    glShaderSource(fragment_shader, 1, &f_source, NULL);
    glCompileShader(fragment_shader);

    auto compilationSuccess = [](GLuint shader, std::string type) -> bool
    {
      int info_log_length = 0;
      GLint compile_success = GL_FALSE;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
      glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_success);

      if (!compile_success)
      {
        char buffer[info_log_length + 1];
        glGetShaderInfoLog(shader, info_log_length, NULL, buffer);
        std::cerr << "ERROR: failed to compile " << type << " shader:\n" << buffer << "\n";
        glDeleteShader(shader);
        return false;
      }
      return true;
    };

    bool vert_success = compilationSuccess(vertex_shader, "vertex");
    bool frag_success = compilationSuccess(fragment_shader, "fragment");

    if (!vert_success || !frag_success)
    {
      glDeleteShader(vertex_shader);
      glDeleteShader(fragment_shader);
      return false;
    }

    glAttachShader(program_id_, vertex_shader);
    glAttachShader(program_id_, fragment_shader);
    glLinkProgram(program_id_);

    GLint link_success = GL_FALSE;
    int program_info_log_length = 0;

    glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &program_info_log_length);
    glGetProgramiv(program_id_, GL_LINK_STATUS, &link_success);

    if (!link_success)
    {
      char buffer[program_info_log_length + 1];
      glGetProgramInfoLog(program_id_, program_info_log_length, NULL, buffer);
      std::cerr << "Error: program failed to link correctly.\n\n" << buffer << "\n";
      glDeleteProgram(program_id_);
      return false;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
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
    } catch (std::exception e)
    {
      std::cerr << "ERROR: file: " << filename << " not successfully read:\n";
      exit(EXIT_FAILURE);
    }

    return shader_source;
  }

  GLuint Shader::getProgramId()
  {
    return program_id_;
  }

  void Shader::useProgram()
  {
    glUseProgram(program_id_);
  }
} // namespace vv