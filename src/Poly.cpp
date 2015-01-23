
// Written By: Roman Larionov

#include "Poly.h"

#include <stdlib.h>

namespace vv
{
namespace graphics
{
    Poly::Poly()
    {
        // TODO: add timers to all poly's. they need to have a living period.
        //       this can be random or strict.

        // this should store the color of the poly, its lifespan, its position,

        // there can be different types of poly's. some that move in different
        // way. it would be a good idea to extend off of this poly class to make
        // specific types of poly's; each with their own special attributes.

        // set a random position and the color equal to the position.

        position[0] = ((rand() % 5) - 5);
        position[1] = ((rand() % 5) - 5);
        position[2] = ((rand() % 5) - 5);

        color[0] = position[0];
        color[1] = position[1];
        color[2] = position[2];

        glGenBuffers(1, &positionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positionBuffer), position, GL_STATIC_DRAW);

        //glGenBuffers(1, &colorBuffer);
		//glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(colorBuffer), color, GL_STATIC_DRAW);
    }


    Poly::~Poly()
    {
        delete[] position;
        delete[] color;
    }

    GLfloat* Poly::getPosition() const
    {
        return this->position;
    }

    GLfloat* Poly::getColor() const
    {
        return this->color;
    }

    void Poly::setPosition(GLfloat* position)
    {
        this->position = position;
    }

    void Poly::setColor(GLfloat* color)
    {
        this->color = color;
    }
}
}
