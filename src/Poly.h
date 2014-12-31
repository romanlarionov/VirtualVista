
// Written By: Roman Larionov

#ifndef VV_POLY_H
#define VV_POLY_H

#include <OpenGL/gl3.h>
#include <vector>
#include <string>

namespace vv
{
namespace graphics
{
    class Poly
    {
        public:
            // Members
            float lifeSpan;

            std::vector<std::string> buffers;

            // Constructor/Destructor
            Poly();
            ~Poly();

            // Functions
            GLfloat* getPosition() const;
            GLfloat* getColor() const;
            void setPosition(GLfloat* position);
            void setColor(GLfloat* color);

		private:

			// OpenGL Buffers
			GLfloat* position;
			GLfloat* color;
    };
}
}

#endif