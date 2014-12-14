
// Written by: Roman Larionov

#ifndef VV_POLY_FACTORY_H
#define VV_POLY_FACTORY_H

#include "Poly.h"

namespace vv
{
namespace graphics
{
    class PolyFactory
    {
    public:

        PolyFactory();
        ~PolyFactory();
        PolyFactory* instance();
        std::unique_ptr<Poly> createPoly();

    private:
        // Members
        PolyFactory* _instance;

    };
}
}

#endif