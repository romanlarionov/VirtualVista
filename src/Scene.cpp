
// Written By: Roman Larionov

#include <OpenGL/gl3.h>
#include <iostream>
#include "Scene.h"

namespace vv
{
    namespace scene
    {
        Scene::Scene()
        {
        }

        Scene::~Scene()
        {
        }

        void Scene::addObjects(vv::graphics::Poly object)
        {
           this->objects.push_back(object);
        }

        void Scene::draw()
        {
            // Loops through each object in the scene and calls their own draw function.
            std::for_each(this->objects.begin(), this->objects.end(),
            [] (vv::graphics::Poly o)
            {
                o.draw();
            });
        }

        void Scene::setGlLocations(GLuint program)
        {
            unsigned int iter;

            // Set all uniform locations.
            std::string uniformNames[0];

            for (iter = 0; iter < uniformNames->size(); iter++)
            {
                GLchar const * currUniform = (GLchar*)uniformNames[iter].c_str();
                GLint loc = glGetUniformLocation(program, currUniform);

                if (loc)
                    this->uniforms[currUniform] = loc;  // Hash Map
                else
                {
                    std::cerr << "ERROR: undefined uniform value for: " << currUniform << std::endl;
                    exit(EXIT_FAILURE);
                }
            }

            // Set all attribute locations.
            std::string attributeNames[] = {"position"};

            for (iter = 0; iter < uniformNames->size(); iter++)
            {
                GLchar const * currAttribute = (GLchar*)uniformNames[iter].c_str();
                GLint loc = glGetAttribLocation(program, currAttribute);

                if (loc)
                    this->uniforms[currAttribute] = loc;  // Hash Map
                else
                {
                    std::cerr << "ERROR: undefined attribute value for: " << currAttribute << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}