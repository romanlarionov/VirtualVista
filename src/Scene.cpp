
// Written By: Roman Larionov

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

        }

    }
}