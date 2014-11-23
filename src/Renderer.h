
// Written By: Roman Larionov

#ifndef SCENE_H
#define SCENE_H

#include "Poly.h"
#include "string"
#include "unordered_map"

namespace vv
{
    namespace app
    {
        class Renderer
        {
            public:
                // Constructor/Destructor
                Renderer(GLuint program);
                ~Renderer();

                // Methods
	            void init();
                void draw();

            private:
                // Members
	            GLuint program;
                std::vector<vv::graphics::Poly> objects;

                std::unordered_map<std::string, GLint> uniforms;
                std::unordered_map<std::string, GLint> attributes;

	            // Functions
				void setGlLocations();
        };
    }
}

#endif