
#ifndef VIRTUALVISTA_SHADER_H
#define VIRTUALVISTA_SHADER_H

#include <string>

#include <glad/glad.h>

#include "Resource.h"

namespace vv
{
  class Shader : public Resource
  {
  public:
    Shader(std::string vert_filename, std::string frag_filename);
    ~Shader();

    GLuint getProgramId();
    void useProgram();
    GLint getUniformLocation(const char *name) const;

  private:
    std::string vert_filename_;
    std::string frag_filename_;
    GLuint program_id_;

    std::string loadShaderFromFile(const std::string filename);
    bool createProgram(std::string vert_source, std::string frag_source);
  };
}

#endif // VIRTUALVISTA_SHADER_H