
// Written By: Roman Larionov

#include "Poly.h"
#include "string"
#include "unordered_map"

namespace vv
{
    namespace scene
    {
        class Scene
        {
            public:
                // Constructor/Destructor
                Scene();
                ~Scene();

                // Methods
                void addObjects(vv::graphics::Poly object);
                void draw();
                void setGlLocations(GLuint program);

            private:
                // Members
                std::vector<vv::graphics::Poly> objects;

                std::unordered_map<std::string, GLint> uniforms;
                std::unordered_map<std::string, GLint> attributes;
        };
    }
}