
#ifndef VIRTUALVISTA_SCENE_H
#define VIRTUALVISTA_SCENE_H

#include <set>

#include "Entity.h"

namespace vv
{
  class Scene
  {
  public:
    Scene();
    ~Scene();

    /* todo: check if 'instantiatePerspectiveCamera' and 'instantiateOrthogonalCamera'
       might be better than 'instantiateCamera(Enum::Perspective)' */
    void instantiateCamera();

    void instantiateModel();

    /* This will come in handy when considering XML/Collada scene structures */
    bool loadSceneFromFile();
    void saveSceneToFile();

  private:
    bool currently_used_;

    std::set<Entity *> entities_;
  };
}

#endif // VIRTUALVISTA_SCENE_H