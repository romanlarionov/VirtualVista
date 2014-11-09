
#include "vector"
#include "OpenGL/gl3.h"

namespace vv
{
namespace graphics
{
    class Poly
    {
        public:
            // Members
            std::vector<GLuint>* buffers;

            // Constructor/Destructor
            Poly();
            ~Poly();

            // Functions
            void draw();
    };
}
}