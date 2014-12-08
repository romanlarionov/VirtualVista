
// Written By: Roman Larionov

#include <OpenGL/gl3.h>
#include <iostream>
#include "Renderer.h"

namespace vv
{
    namespace app
    {
        Renderer::Renderer(GLuint program) :
	        program(program)
        {
        }

        Renderer::~Renderer()
        {
        }

	    void Renderer::init()
	    {
		    setGlLocations();


	    }

        void Renderer::draw()
        {
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	        glUseProgram(program);

            // Loops through each object in the scene and calls their own draw function.
            std::for_each(this->objects.begin(), this->objects.end(),
            [] (vv::graphics::Poly o)
            {
                o.draw();
            });
        }

        void Renderer::setGlLocations()
        {
            unsigned int iter;

            // Set all uniform locations.
            std::string uniformNames[0];

            for (iter = 0; iter < uniformNames->size(); iter++)
            {
                GLchar const* currUniform = (GLchar*)uniformNames[iter].c_str();
                GLint loc = glGetUniformLocation(program, currUniform);

                if (loc)
                    this->uniforms[currUniform] = loc;  // Hash Map
                else
                {
                    std::cerr << "ERROR: undefined uniform value for: " << currUniform << "\n";
                    exit(EXIT_FAILURE);
                }
            }

            // Set all attribute locations.
            std::string attributeNames[] = {"position"};

            for (iter = 0; iter < attributeNames->size(); iter++)
            {
                GLchar const* currAttribute = (GLchar*)attributeNames[iter].c_str();
                GLint loc = glGetAttribLocation(program, currAttribute);

                if (loc)
                    this->uniforms[currAttribute] = loc;  // Hash Map
                else
                {
                    std::cerr << "ERROR: undefined attribute value for: " << currAttribute << "\n";
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}