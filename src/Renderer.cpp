
// Written By: Roman Larionov

#include <OpenGL/gl3.h>
#include <iostream>
#include "Renderer.h"

namespace vv
{
    namespace app
    {
        Renderer::Renderer(GLuint program) :
                program(program),
                maxLivingPolys(4)
        {
            // TODO: create object pool of poly's and recycle them when needed.
        }


        Renderer::~Renderer()
        {
        }


        void Renderer::init()
        {
            // Setup uniforms/attributes.
            this->findActiveUniforms();
            this->findActiveAttributes();
            this->setGlLocations();

            int iter;
            for (iter = 0; iter < maxLivingPolys; iter++)
            {
                this->createPoly();
            }
        }


        // init calls this to create first wave of polys.
        // then called by updatePolys to create new ones.
        bool Renderer::createPoly()
        {
            bool creationSuccess = false;

            if (currentLivingPolys < maxLivingPolys)
            {
                vv::graphics::Poly instance;
                objects.push_back(instance);
                creationSuccess = true;
            }

            return creationSuccess;
        }


        bool Renderer::updatePolys()
        {
            bool updateSuccess = false;
            unsigned int iter;
            for (iter = 0; iter < objects.size(); iter++)
            {
                // Update poly position/color/other stuff.
                // TODO: Actually fill in with things to update.
            }

            return updateSuccess;
        }


        void Renderer::render()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(program);

            this->updatePolys();

            // Loops through each object in the scene and calls their own draw function.
            std::for_each(this->objects.begin(),
                    this->objects.end(),
                    [](vv::graphics::Poly o)
                    {
                        o.draw();
                    });
        }


        void Renderer::findActiveAttributes()
        {
            const std::vector<std::string> attributeNames = {"position"};
            GLsizei maxAttributeCharacters = 20;
            GLint* numActiveAttributes = 0;
            glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, numActiveAttributes);

			GLint i;
			GLsizei length;
			GLint size;
			GLenum type;
			GLchar* name;
			for (i = 0; i < (*numActiveAttributes); i++)
			{
				// Returns the length, size, type, and name of the attribute.
				glGetActiveAttrib(program, i, maxAttributeCharacters, &length, &size, &type, name);

				// If the attribute is on the list of valid attributes.
				if ((name != NULL) &&
						(std::find(attributeNames.begin(), attributeNames.end(), name) != attributeNames.end()))
					activeAttributes.push_back(name);
				else
				{
					std::cerr << "ERROR: attribute " << name << " is declared in " <<
							"the program but not supported by the renderer.\n";
					// TODO: debating whether this exit should stay. do some testing.
					exit(EXIT_FAILURE);
				}
            }
        }


        void Renderer::findActiveUniforms()
        {
            const std::vector<GLchar*> uniformNames = {};
            GLsizei maxUniformCharacters = 20;
            GLint* numActiveUniforms = 0;
            glGetProgramiv(program, GL_ACTIVE_UNIFORMS, numActiveUniforms);

			GLint i;
			GLsizei length;
			GLint size;
			GLenum type;
			GLchar* name;
			for (i = 0; i < (*numActiveUniforms); i++)
			{
				// Returns the length, size, type, and name of the attribute.
				glGetActiveAttrib(program, i, maxUniformCharacters, &length, &size, &type, name);

				// If the attribute is on the list of valid attributes.
				if ((name != NULL) &&
						(std::find(uniformNames.begin(), uniformNames.end(), name) != uniformNames.end()))
					activeUniforms.push_back(name);
				else
				{
					std::cerr << "ERROR: uniform " << name << " is declared in " <<
							"the program but not supported by the renderer.\n";
					// TODO: debating whether this exit should stay. do some testing.
					exit(EXIT_FAILURE);
				}
            }
        }


        void Renderer::setGlLocations()
        {
            unsigned int iter;

            // Set all uniform locations.
            for (iter = 0; iter < activeUniforms.size(); iter++)
            {
                GLchar const *currUniform = activeUniforms.at(iter);
                GLint loc = glGetUniformLocation(program, currUniform);
				this->uniformLocations[currUniform] = loc;  // Hash Map
            }

            // Set all attribute locations.
            for (iter = 0; iter < activeAttributes.size(); iter++)
            {
                GLchar const *currAttribute = activeAttributes.at(iter);
                GLint loc = glGetAttribLocation(program, currAttribute);
				this->attributeLocations[currAttribute] = loc;  // Hash Map
            }
        }
    }
}






