
#include "Renderer.h"
#include "ShaderManager.h"

namespace vv
{
  Renderer* Renderer::renderer_singleton_ = nullptr;
  std::set<Light *> Renderer::lights_;
  std::set<Model *> Renderer::models_;

  Renderer::Renderer()
  {
  }


  Renderer* Renderer::instance()
  {
   if (!renderer_singleton_)
     renderer_singleton_ = new Renderer;

    return renderer_singleton_;
  }


  bool Renderer::init()
  {

  }


  void Renderer::update()
  {

  }


  void Renderer::render(Camera *camera)
  {
    camera->update();

    // Render light sources first
    ShaderManager::instance()->getLightCubeShader()->useProgram();
    camera->updateUniforms(ShaderManager::instance()->getLightCubeShader());

    for (auto l : lights_)
      if (l->canRender())
        l->render();

    // Render models
    ShaderManager::instance()->getModelShader()->useProgram();
    camera->updateUniforms(ShaderManager::instance()->getModelShader());

    for (auto l : lights_)
      l->update(ShaderManager::instance()->getModelShader());

    for (auto m : models_)
      m->render();
  }


  void Renderer::addToRenderList(Light *light)
  {
    lights_.insert(light);
  }


  void Renderer::removeFromRenderList(Light *light)
  {
    lights_.erase(light);
  }


  void Renderer::addToRenderList(Model *model)
  {
    models_.insert(model);
  }


  void Renderer::removeFromRenderList(Model *model)
  {
    models_.erase(model);
  }
} // namespace vv