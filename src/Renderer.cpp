
// Written By: Roman Larionov

#include "Renderer.h"

//#include <OpenGL/gl3.h>
#include <iostream>

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
                livingPolyList.push_back(instance);
                currentLivingPolys++;
                creationSuccess = true;
            }

            return creationSuccess;
        }


        bool Renderer::updatePolys()
        {
            bool updateSuccess = false;
            int iter;
            for (iter = 0; iter < currentLivingPolys; iter++)
            {
                // Update poly position/color/other stuff.
                // TODO: Actually fill in with things to update.

                //  if poly->lifespan >= maxpolylifespan do
                //      remove poly from livingpolylist
                //      currentlivingpolys -= 1
                //      add poly back to object pool
                //  endif
            }

            return updateSuccess;
        }


        void Renderer::render()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(program);

            this->updatePolys();
            // Loop through all Poly's and render them.
            std::for_each(livingPolyList.begin(), livingPolyList.end(), [](vv::graphics::Poly poly) {
                // render poly.
            });
        }


        void Renderer::findActiveAttributes()
        {
            const std::vector<std::string> attributeNames = {"position"};
            GLsizei maxAttributeCharacters = 20;
            GLint* numActiveAttributes = 0;
            glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, numActiveAttributes);

			GLint i;
			GLchar* name;
			for (i = 0; i < (*numActiveAttributes); i++)
			{
				// Returns the length, size, type, and name of the attribute.
				glGetActiveAttrib(program, i, maxAttributeCharacters, NULL, NULL, NULL, name);

				// If the attribute is on the list of valid attributes.
				if ((name != NULL) &&
						(std::find(attributeNames.begin(), attributeNames.end(), name) != attributeNames.end()))
                {
                    GLint loc = glGetAttribLocation(program, name);
					this->attributeLocations[name] = loc;  // Hash Map
                }
				else
				{
					std::cerr << "ERROR: attribute " << name << " is declared in " <<
							"the program but not supported by the renderer.\n";
					// TODO: debating whether this exit should stay. do some testing.
					exit(EXIT_FAILURE);
				}
            }
        };


        void Renderer::findActiveUniforms()
        {
            const std::vector<std::string> uniformNames = {"color"};
            GLsizei maxUniformCharacters = 20;
            GLint* numActiveUniforms = 0;
            glGetProgramiv(program, GL_ACTIVE_UNIFORMS, numActiveUniforms);

			GLint i;
			GLchar* name;
			for (i = 0; i < (*numActiveUniforms); i++)
			{
				// Returns the length, size, type, and name of the attribute.
				glGetActiveAttrib(program, i, maxUniformCharacters, NULL, NULL, NULL, name);

				// If the attribute is on the list of valid attributes.
				if ((name != NULL) &&
						(std::find(uniformNames.begin(), uniformNames.end(), name) != uniformNames.end()))
                {
					GLint loc = glGetUniformLocation(program, name);
					this->uniformLocations[name] = loc;  // Hash Map
                }
				else
				{
					std::cerr << "ERROR: uniform " << name << " is declared in " <<
							"the program but not supported by the renderer.\n";
					// TODO: debating whether this exit should stay. do some testing.
					exit(EXIT_FAILURE);
				}
            }
        }

        void Renderer::setUniforms()
        {
            for (auto iter = livingPolyList.begin(); iter != livingPolyList.end(); iter++)
            {
                // TODO: replace with a more general code base.
                glUniform3f(uniformLocations["color"], (*iter).getPosition()[0],
                        (*iter).getPosition()[1], (*iter).getPosition()[2]);
            }
        }

        void Renderer::setAttributes()
        {
            GLuint attributeCounter = 0;
			for (auto iter = livingPolyList.begin(); iter != livingPolyList.end(); iter++)
            {
                GLuint loc = static_cast<GLuint>(attributeLocations["position"]);
                GLint numComponents = sizeof((*iter).getPosition())/sizeof((*iter).getPosition()[0]);
                glEnableVertexAttribArray(attributeCounter);
                glBindBuffer(GL_ARRAY_BUFFER, loc);
                glVertexAttribPointer(loc, numComponents, GL_FLOAT, GL_FALSE, 0, (void*)0);
                attributeCounter++;
            }

            attributeCounter = 0;
        }
    }
}






