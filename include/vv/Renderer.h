
#ifndef VIRTUALVISTA_RENDERER_H
#define VIRTUALVISTA_RENDERER_H

#include "Scene.h"

namespace vv
{
  class Renderer
  {
  public:
    static Renderer* instance();

    bool init();
    void update();
    void render(Scene *scene);

  private:
    static Renderer *renderer_singleton_;

    Renderer();
    Renderer(Renderer const &) {};
    Renderer& operator=(Renderer const &) {};
  };
}

#endif // VIRTUALVISTA_RENDERER_H