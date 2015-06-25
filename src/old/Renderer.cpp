/*
// Written By: Roman Larionov

#include "Renderer.h"

#include <OpenGL/g3.h>
#include <stdlib.h>
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
            //glUseProgram(program);
            // Setup uniforms/attributes.
            this->findActiveAttributes();
            this->findActiveUniforms();

            //int iter;
            //for (iter = 0; iter < maxLivingPolys; iter++)
            //{
            //    this->createPoly();
            //}
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
            GLfloat* position = new GLfloat[3];
			GLfloat* color = new GLfloat[3];

            bool updateSuccess = false;
            for (auto iter = livingPolyList.begin(); iter != livingPolyList.end(); iter++)
            {
                position[0] = color[0] = rand() % 5;
                position[1] = color[1] = rand() % 5;
                position[2] = color[2] = rand() % 5;

                iter->setPosition(position);
                iter->setColor(color);

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
            glUseProgram(this->program);

            updatePolys();
            setUniforms();
            setAttributes();

            // Loop through all Poly's and render them.
            std::for_each(livingPolyList.begin(), livingPolyList.end(), [](vv::graphics::Poly poly) {
                // render poly.
                // TODO: switch to more generic start and end of mesh buffer.
                glDrawArrays(GL_TRIANGLES, 0, 3);
            });
        }


        void Renderer::findActiveAttributes()
        {
            const std::vector<std::string> attributeNames = {"position"};
            GLsizei maxAttributeCharacters = 20;
            GLint* numActiveAttributes = new GLint;
            glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, numActiveAttributes);

			GLint i;
			GLchar* name = new GLchar[40];
			for (i = 0; i < (*numActiveAttributes); i++)
			{
				// Returns the length, size, type, and name of the attribute.
				glGetActiveAttrib(program, i, maxAttributeCharacters, NULL, NULL, NULL, name);

				// If the attribute is on the list of valid attributes.
				if ((name != nullptr) &&
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

            delete numActiveAttributes;
            delete[] name;
        };


        void Renderer::findActiveUniforms()
        {
            const std::vector<std::string> uniformNames = {"color"};
            GLsizei maxUniformCharacters = 20;
            GLint* numActiveUniforms = new GLint;
            glGetProgramiv(program, GL_ACTIVE_UNIFORMS, numActiveUniforms);

			GLuint i;
			GLchar* name = new GLchar[40];
			for (i = 0; i < (*numActiveUniforms); i++)
			{
				// Returns the length, size, type, and name of the attribute.
                glGetActiveUniform(program, i, maxUniformCharacters, NULL, NULL, NULL, name);

				// If the attribute is on the list of valid attributes.
				if ((name != nullptr) &&
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

            delete numActiveUniforms;
            delete[] name;
        }

        void Renderer::setUniforms()
        {
            for (auto iter = livingPolyList.begin(); iter != livingPolyList.end(); iter++)
            {
                // TODO: replace with a more general code base.
                glUniform3fv(uniformLocations["color"], 3, iter->getColor());
            }
        }

        void Renderer::setAttributes()
        {
            GLuint attributeCounter = 0;
			for (auto iter = livingPolyList.begin(); iter != livingPolyList.end(); iter++)
            {
                GLuint loc = static_cast<GLuint>(attributeLocations["position"]);
                GLint numComponents = 3; // TODO: switch to more generic
                glEnableVertexAttribArray(attributeCounter);
                glBindBuffer(GL_ARRAY_BUFFER, loc);
                glVertexAttribPointer(loc, numComponents, GL_FLOAT, GL_FALSE, 0, (void*)0);
                attributeCounter++;
            }

            attributeCounter = 0;
        }
    }
}




*/

