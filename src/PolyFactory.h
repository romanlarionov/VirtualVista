
// Written by: Roman Larionov

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