
#ifndef VIRTUALVISTA_SHADER_H
#define VIRTUALVISTA_SHADER_H

#include <string>

#include <glad/glad.h>

#include "Resource.h"

namespace vv
{
  typedef std::string ShaderHandle;

  class Shader : public Resource
  {
  public:
    Shader(std::string vert_filename, std::string frag_filename);
    ~Shader();

    bool init();

    GLuint getProgramId() const;
    void useProgram();
    GLint getUniformLocation(std::string name) const;

  private:
    GLuint program_id_;

    std::string loadShaderFromFile(const std::string filename);
    bool createProgram(std::string vert_source, std::string frag_source);
  };
}

#endif // VIRTUALVISTA_SHADER_H