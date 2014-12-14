
#ifndef VV_POLY_H
#define VV_POLY_H

#include <OpenGL/OpenGL.h>
#include "vector"

namespace vv
{
namespace graphics
{
    class Poly
    {
        public:
            // Members
            std::vector<GLuint> buffers;

            // Constructor/Destructor
            Poly();
            ~Poly();

            // Functions
            void draw();
            void initPoly();
    };
}
}

#endif