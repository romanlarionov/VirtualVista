
#ifndef VIRTUALVISTA_RENDERER_H
#define VIRTUALVISTA_RENDERER_H

#include <set>

#include "Camera.h"
#include "Model.h"
#include "Light.h"

namespace vv
{
  class Renderer
  {
    friend class Light;
    friend class Model;

  public:
    static Renderer* instance();

    bool init();
    void update();
    void render(Camera *camera);

  private:
    static Renderer *renderer_singleton_;

    static std::set<Light *> lights_;
    static std::set<Model *> models_;

    Renderer();
    Renderer(Renderer const &);
    Renderer& operator=(Renderer const &);

    void addToRenderList(Light *light);
    void removeFromRenderList(Light *light);
    void addToRenderList(Model *model);
    void removeFromRenderList(Model *model);
  };
}

#endif // VIRTUALVISTA_RENDERER_H