
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
    virtual ~Resource() {}

  private:
    size_t use_count_;
    
  protected:
    Handle handle_;
    std::string file_path_;
    std::string file_name_;

    Resource(std::string path, std::string name);
    
  };
}

#endif // VIRTUALVISTA_RESOURCE_H