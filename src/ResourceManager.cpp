
#include "vv/ResourceManager.h"

namespace vv
{
  /////////////////////////////////////////////////////////////////////// public
  ResourceManager::ResourceManager()
  {
  }


  ResourceManager::~ResourceManager()
  {
    clearResources();
  }


  Handle ResourceManager::addShader(std::string path, std::string name)
  {
    if (path.empty() || name.empty()) return "";

    // if shader already exists, return it's handle
    if (shader_buffer_[path + name])
      return shader_buffer_[path + name]->handle_;

    // create shader
    Shader *shader = new Shader(path, name);

    if (!shader->init())
    {
      delete shader;
      return "";
    }

    // update internal storage parameters
    shader->use_count_++;
    shader_buffer_[shader->handle_] = shader;

    return shader->handle_;
  }


  void ResourceManager::removeShader(Handle handle)
  {
    if (handle.empty()) return;

    Shader *shader = shader_buffer_[handle];
    shader->use_count_--;

    // todo: see if there's better way of timing deletion than simply when the resource isn't being used anymore
    if (shader->use_count_ == 0)
    {
      if (shader) // todo: see if erase leaves a dangling pointer
      {
        delete shader;
        shader = NULL;
      }
      shader_buffer_.erase(handle);
    }
  }

  
  bool ResourceManager::loadMeshFromFile(std::string path, std::string name)
  {
    return true;
  }


  bool ResourceManager::loadTextureFromFile(std::string path, std::string name)
  {
    return true;
  }

  
  void ResourceManager::clearResources()
  {
    // todo: find out if this deletion is necessary
    for (auto s : shader_buffer_)
      delete s.second;

    shader_buffer_.clear();
  }
  ////////////////////////////////////////////////////////////////////// private
} // namespace vv