
#ifndef VIRTUALVISTA_SHADER_H
#define VIRTUALVISTA_SHADER_H

#include "glew.h"
#include <vector>
#include <string>

namespace vv
{
namespace vis
{
    class Shader
    {
    public:
        Shader(std::string verg_filename, std::string frag_filename);
        ~Shader();

        bool init();

        GLuint getProgramId() { return program_id; }
        void setProgramId(GLuint id) { program_id = id; }

    private:

        std::string v_name;
        std::string f_name;
        GLuint program_id;

        std::string loadShader(const std::string filename);
        bool createProgram(std::string vert_filename, std::string frag_filename);
    };
}
}

#endif // VIRTUALVISTA_SHADER_H
