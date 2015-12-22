
#include "vv/Entity.h"

namespace vv
{
  /////////////////////////////////////////////////////////////////////// public
  Entity::Entity() :
    is_visible_(false),
    has_geometry_(false)
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
    return has_geometry_ && is_visible_;
  }


  void Entity::setVisiblity(bool visibility)
  {
    is_visible_ = visibility;
  }


  ////////////////////////////////////////////////////////////////////// private
} // namespace vv