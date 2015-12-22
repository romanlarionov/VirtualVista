
#include <set>

#include "vv/Renderer.h"
#include "vv/ResourceManager.h"

namespace vv
{
  Renderer* Renderer::renderer_singleton_ = nullptr;

  /////////////////////////////////////////////////////////////////////// public
  Renderer* Renderer::instance()
  {
    if (!renderer_singleton_)
     renderer_singleton_ = new Renderer;

    return renderer_singleton_;
  }


  bool Renderer::init()
  {
    return false;
  }


  void Renderer::update()
  {

  }


  void Renderer::render(Scene *scene)
  {

    // Render light sources first
    Shader *shader = ResourceManager::instance()->getLightCubeShader();
    shader->useProgram();
    camera->setUniforms(shader);

    std::set<Light *> lights = ResourceManager::instance()->getLights();
    std::set<Model *> models = ResourceManager::instance()->getModels();

    for (auto l : lights)
      if (l->isRenderable())
        l->render();

    // Render models
    shader = ResourceManager::instance()->getModelShader();
    shader->useProgram();
    camera->setUniforms(shader);

    int i = 0;
    for (auto l : lights)
      l->setUniforms(i++, shader);

    for (auto m : models)
      m->render();
  }


  ////////////////////////////////////////////////////////////////////// private
  Renderer::Renderer()
  {
  }
} // namespace vv