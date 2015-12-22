
#include "vv/Entity.h"

namespace vv
{
  /////////////////////////////////////////////////////////////////////// public
  Entity::Entity() :
    can_be_rendered_(false),
    is_visible_(false)
  {
    transform_ = new Transform;
  }


  Entity::~Entity()
  {
    delete transform_;
  }


  Transform* Entity::getTransform()
  {
    return transform_;
  }


  bool Entity::isRenderable()
  {
    return can_be_rendered_ && is_visible_;
  }


  bool Entity::isVisible()
  {
    return is_visible_;
  }


  void Entity::setVisiblity(bool visibility)
  {
    is_visible_ = visibility;
  }


  ////////////////////////////////////////////////////////////////////// private
} // namespace vv