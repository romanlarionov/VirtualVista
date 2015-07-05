
#ifndef VIRTUALVISTA_SHADER_H
#define VIRTUALVISTA_SHADER_H

#ifndef VIRTUALVISTA_APPLICATION_H
  #include <GL/glew.h>
#endif

#include <string>

namespace vv
{
  class Shader
  {
  public:
    Shader(std::string vert_filename, std::string frag_filename);
    ~Shader();

    GLuint getProgramId();
    void useProgram();

  private:
    GLuint program_id_;

    std::string loadShader(const std::string filename);
    bool createProgram(std::string vert_source, std::string frag_source);
  };
}

#endif // VIRTUALVISTA_SHADER_H