
#ifndef VIRTUALVISTA_RESOURCE_H
#define VIRTUALVISTA_RESOURCE_H

#include <string>

namespace vv
{
  typedef std::string Handle;

  class Resource
  {
    friend class ResourceManager;

  public:
    virtual ~Resource()
    {
    }

  private:
    size_t use_count_;
    
  protected:
    Handle handle_;
    std::string file_path_;
    std::string file_name_;

    Resource(std::string path, std::string name) :
      use_count_(0),
      file_path_(path),
      file_name_(name)
    {
      handle_ = file_path_ + file_name_; // todo: find better way of creating handle (or rename because this can get confusing)
    }
  };
}

#endif // VIRTUALVISTA_RESOURCE_H