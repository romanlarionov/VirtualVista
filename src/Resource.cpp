
#include "vv/Resource.h"

namespace vv
{
  /////////////////////////////////////////////////////////////////////// public
  Resource::Resource(std::string path, std::string name) :
    use_count_(0),
    file_path_(path),
    file_name_(name)
  {
    handle_ = file_path_ + file_name_; // todo: find better way of creating handle (or rename because this can get confusing)
  }
} // namespace vv