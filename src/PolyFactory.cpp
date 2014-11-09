
// Written by: Roman Larionov

#include "PolyFactory.h"

namespace vv
{
namespace graphics
{
    PolyFactory::PolyFactory()
    {
    }

    PolyFactory::~PolyFactory()
    {
        delete _instance;
    }

    PolyFactory* PolyFactory::instance()
    {
        if (!_instance)
        {
            _instance = new PolyFactory();
        }

        return _instance;
    }

    void PolyFactory::createPoly()
    {
        //std::unique_ptr<Poly> poly = new Poly();


        //return poly;
    }
}
}

