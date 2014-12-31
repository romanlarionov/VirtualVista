
// Written By: Roman Larionov

#ifndef VV_RENDERER_H
#define VV_RENDERER_H

#include "Poly.h"
#include "string"
#include "vector"
#include "unordered_map"
#include "list"

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
                void render();

            private:
                // Members
	            GLuint program;
                const unsigned int maxLivingPolys;
                unsigned int currentLivingPolys;

                std::list<vv::graphics::Poly> livingPolyList;

                std::unordered_map<std::string, GLint> uniformLocations;
                std::unordered_map<std::string, GLint> attributeLocations;

	            // Functions
                bool createPoly();
                bool updatePolys();

                void findActiveAttributes();
                void findActiveUniforms();
                void setUniforms();
                void setAttributes();
        };
    }
}

#endif