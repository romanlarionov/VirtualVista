
#ifndef VIRTUALVISTA_SHADER_H
#define VIRTUALVISTA_SHADER_H

#ifndef VIRTUALVISTA_APPLICATION_H
  #include <GL/glew.h>
#endif

namespace vv
{
    class Shader
    {
    public:
        Shader(std::string verg_filename, std::string frag_filename);
        ~Shader();

        void useProgram() { glUseProgram(program_id); }

    private:

        GLuint program_id;

        std::string loadShader(const std::string filename);
        bool createProgram(std::string vert_source, std::string frag_source);
    };
}

#endif // VIRTUALVISTA_SHADER_H
