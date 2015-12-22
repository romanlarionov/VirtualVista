
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
    bool isVisible();
    void setVisiblity(bool visibility);

    virtual void render() = 0;

  private:

  protected:
    bool can_be_rendered_; // set on initialization, cannot be changed
    bool is_visible_; // dynamically set, used for culling operations

    Transform *transform_;
  };
}

#endif // VIRTUALVISTA_ENTITY_H