
#ifndef VIRTUALVISTA_RENDERABLEOBJECT_H
#define VIRTUALVISTA_RENDERABLEOBJECT_H

#include "Transform.h"

namespace vv
{
    class RenderableObject : public Transform
    {
    public:
        RenderableObject();
        ~RenderableObject();

        virtual void render() = 0;

    private:
    };
}

#endif // VIRTUALVISTA_RENDERABLEOBJECT_H