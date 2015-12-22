
#ifndef VIRTUALVISTA_ENTITY_H
#define VIRTUALVISTA_ENTITY_H

#include "Transform.h"

namespace vv
{
  class Entity
  {
  public:
    Entity();
    ~Entity();

    Transform* getTransform();
    bool isRenderable();
    void setVisiblity(bool visibility);

    virtual void render() = 0;

  private:
    bool is_visible_; /* lock for visibility within view frustum */
    bool has_geometry_; /* determines whether entity has anything to draw */

    Transform *transform_;

  };
}

#endif // VIRTUALVISTA_ENTITY_H