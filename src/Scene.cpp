
#include "Scene.h"

namespace vv
{
    /////////////////////////////////////////////////////////////////////// public
    Scene::Scene()
    {

    }


    Scene::~Scene()
    {

    }


    void Scene::manage(Light *light)
    {
        lights.insert(light);
    }


    void Scene::manage(Model *model)
    {
        model.insert(model);
    }


    void Scene::manage(Camera *camera)
    {
        camera_ = camera;
    }


    void Scene::stopManaging(Light *light)
    {
        lights_.erase(light);
    }


    void Scene::stopManaging(Model *model)
    {
        models.erase(model);
    }


    void Scene::stopManaging(Camera *camera)
    {
        camera_ = nullptr;
    }


    ////////////////////////////////////////////////////////////////////// private
} // namespace vv