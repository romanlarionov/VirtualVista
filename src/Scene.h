
// Written By: Roman Larionov

#include "PolyFactory.h"

namespace vv
{
    namespace scene
    {
        class Scene
        {
            public:

            // Members
            std::vector<vv::graphics::Poly> objects;

            // Constructor/Destructor
            Scene();
            ~Scene();

            // Methods
            void addObjects(vv::graphics::Poly object);
            void draw();
        };
    }
}