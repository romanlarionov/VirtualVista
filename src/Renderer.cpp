
#include "Renderer.h"
#include "ShaderManager.h"

namespace vv
{
  Renderer* Renderer::renderer_singleton_ = nullptr;
  std::set<Light *> Renderer::lights_;
  std::set<Model *> Renderer::models_;

  /////////////////////////////////////////////////////////////////////// public
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
    // Render light sources first
    Shader *shader = ShaderManager::instance()->getLightCubeShader();
    shader->useProgram();
    camera->setUniforms(shader);

    for (auto l : lights_)
      if (l->canRender())
        l->render();

    // Render models
    shader = ShaderManager::instance()->getModelShader();
    shader->useProgram();
    camera->setUniforms(shader);

    int i = 0;
    for (auto l : lights_)
      l->setUniforms(i++, shader);

    for (auto m : models_)
      m->render();
  }


  ////////////////////////////////////////////////////////////////////// private
  Renderer::Renderer()
  {
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