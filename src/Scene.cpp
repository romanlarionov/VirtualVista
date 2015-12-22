
#include "vv/Scene.h"

namespace vv
{
  /////////////////////////////////////////////////////////////////////// public
  Scene::Scene() :
    is_current_(false)
  {
  }


  Scene::~Scene()
  {
  }


  void Scene::manage(Light *light)
  {
    lights_.insert(light);
  }


  void Scene::manage(Model *model)
  {
    models_.insert(model);
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
    models_.erase(model);
  }


  void Scene::stopManaging(Camera *camera)
  {
    camera_ = nullptr;
  }


  void Scene::setCurrent()
  {
    is_current_ = true;
  }


  ////////////////////////////////////////////////////////////////////// private
} // namespace vv